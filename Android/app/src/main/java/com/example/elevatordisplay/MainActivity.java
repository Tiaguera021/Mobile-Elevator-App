package com.example.elevatordisplay;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener, Network.ElevatorEventListener{
    private TextView cardDisplay;
    private Button btn1, btn2, btn3;
    private Network network;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        cardDisplay = findViewById(R.id.tvDisplay);
        btn1 = findViewById(R.id.btn1);
        btn2 = findViewById(R.id.btn2);
        btn3 = findViewById(R.id.btn3);

        btn1.setOnClickListener(this);
        btn2.setOnClickListener(this);
        btn3.setOnClickListener(this);

        network = new Network(this);
        network.connect();
    }

    @Override
    public void onClick(View v){
        int id = v.getId();

        if (id == R.id.btn1){
            network.requestFloor("1");
        } else if (id == R.id.btn2){
            network.requestFloor("2");
        } else if (id == R.id.btn3){
            network.requestFloor("3");
        }

    }

    @Override
    public void onFloorReceived(String floor){
        runOnUiThread(() -> cardDisplay.setText(floor));
    }

    @Override
    public void onConnectionStatusChanged(boolean isConnected){
        runOnUiThread(() -> {
            String message = isConnected ? "Connected to the elevator!" : "Fail in the MQTT connection!";
            Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
        });
    }

    @Override
    protected void onDestroy(){
        super.onDestroy();
        if (network != null){
            network.disconnect();
        }
    }
}