package com.example.elevatordisplay;

import android.os.Build;
import android.util.Log;
import com.hivemq.client.mqtt.MqttClient;
import com.hivemq.client.mqtt.mqtt3.Mqtt3AsyncClient;
import java.nio.charset.StandardCharsets;
import java.util.UUID;
import com.example.elevatordisplay.BuildConfig;

public class Network {
    private static final String TAG = "MQTT";
    private static final String BROKER_HOST = BuildConfig.MQTT_BROKER_HOST;
    private static final int BROKER_PORT = BuildConfig.MQTT_PORT;
    private static final String TOPIC_COMMAND = BuildConfig.MQTT_TOPIC_COMMAND;
    private static final String TOPIC_STATUS = BuildConfig.MQTT_TOPIC_STATUS;

    private final Mqtt3AsyncClient client;
    private final ElevatorEventListener listener;

    public interface ElevatorEventListener{
        void onFloorReceived(String floor);
        void onConnectionStatusChanged(boolean isConnected);
    }

    public Network(ElevatorEventListener listener){
        this.listener = listener;
        this.client = MqttClient.builder()
                .useMqttVersion3()
                .identifier("Android_Elevator_" + UUID.randomUUID().toString())
                .serverHost(BROKER_HOST)
                .serverPort(BROKER_PORT)
                .buildAsync();
    }

    public void connect(){
        client.connect().whenComplete((connAck, throwable) -> {
            if (throwable != null){
                Log.e(TAG, "Fail to connect on HiveMQ", throwable);
                if (listener != null){
                    listener.onConnectionStatusChanged(false);
                }
            } else{
                Log.d(TAG, "Connected successfully to HiveMQ!");
                if (listener != null){
                    listener.onConnectionStatusChanged(true);
                }
                subscribeToStatus();
            }
        });
    }

    private void subscribeToStatus(){
        client.subscribeWith()
                .topicFilter(TOPIC_STATUS)
                .callback(publish -> {
                    String currentFloor = new String(publish.getPayloadAsBytes(), StandardCharsets.UTF_8);
                    Log.d(TAG, "Floor received by ESP32: " + currentFloor);
                    if (listener != null){
                        listener.onFloorReceived(currentFloor);
                    }
                })
                .send();
    }

    public void requestFloor(String targetFloor){
        if (!client.getState().isConnected()){
            Log.w(TAG, "Client disconnected, not possible to send the command!");
            return;
        }

        client.publishWith()
                .topic(TOPIC_COMMAND)
                .payload(targetFloor.getBytes(StandardCharsets.UTF_8))
                .send()
                .whenComplete((publish, throwable) -> {
                    if (throwable != null){
                        Log.e(TAG, "Fail to publish the floor " + targetFloor, throwable);
                    } else {
                        Log.d(TAG, "Command to the floor " + targetFloor + "send successfully!");
                    }
                });
    }

    public void disconnect(){
        if (client != null && client.getState().isConnected()){
            client.disconnect();
        }
    }
}
