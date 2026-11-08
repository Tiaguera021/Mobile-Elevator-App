package com.example.elevatordisplay;

import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import android.widget.Button;
import android.widget.TextView;
import android.view.View;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    private TextView cardDisplay;
    private Button btn1, btn2, btn3;

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
    }

    @Override
    public void onClick(View v){
        int id = v.getId();
        String selectedValue = "";

        if (id == R.id.btn1){
            selectedValue = "1";
        } else if (id == R.id.btn2){
            selectedValue = "2";
        } else if (id == R.id.btn3){
            selectedValue = "3";
        }

        if(!selectedValue.isEmpty()){
            cardDisplay.setText(selectedValue);

            //Here we gonna do the communication with ESP32 later
        }
    }
}