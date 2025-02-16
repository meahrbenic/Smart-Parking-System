package com.example.smartparkingsystem

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.ImageView
import android.widget.ProgressBar
import android.widget.TextView
import org.eclipse.paho.android.service.MqttAndroidClient
import org.eclipse.paho.client.mqttv3.*

class MainActivity : AppCompatActivity() {
    var client: MqttAndroidClient? = null
    lateinit var brojSlobodnihMjesta : TextView
    lateinit var brojZauzetihMjesta : TextView

    private var maxBroj = 1
    private var zauzeti : Int = 0

    fun provjeSignal(s: String) {
        if(s.toInt() == 1) {
            maxBroj--
            zauzeti++
            brojSlobodnihMjesta.setText(maxBroj.toString())
            brojZauzetihMjesta.setText(zauzeti.toString())

        }
        else {
            if(zauzeti > 0 && maxBroj < 1) {
                maxBroj++
                zauzeti--
            }
            brojSlobodnihMjesta.setText(maxBroj.toString())
            brojZauzetihMjesta.setText(zauzeti.toString())
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {

        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        brojSlobodnihMjesta = findViewById<TextView>(R.id.brojSlobodnihID)
        brojZauzetihMjesta = findViewById<TextView>(R.id.brojZauzetihID)


        client = MqttAndroidClient(getApplicationContext(), "tcp://broker.hivemq.com", MqttClient.generateClientId());

        val op: MqttConnectOptions = MqttConnectOptions();
        op.setCleanSession(true)
        
        client!!.setCallback(object : MqttCallback {
            override fun connectionLost(cause: Throwable?) {
                Log.i("TAG", "connection lost")
            }

            override fun messageArrived(topic: String?, message: MqttMessage?) {
                if (topic!!.contains("projekat/senzor")) {
                    provjeSignal(String(message!!.getPayload()));
                }
                Log.i("TAG", "ovdje je")
            }

            override fun deliveryComplete(token: IMqttDeliveryToken?) {
                Log.i("TAG", "msg delivered")
            }

        })

        try {
            client!!.connect(op, null, object : IMqttActionListener {
                override fun onSuccess(asyncActionToken: IMqttToken?) {
                    Log.i("TAG", "connect succeed")
                    subscribeTopic("projekat/senzor")
                }

                override fun onFailure(asyncActionToken: IMqttToken?, exception: Throwable?) {
                    Log.i("TAG", "connect failed")
                }
            })
        }
        catch(e: MqttException) {
            e.printStackTrace()
        }
    }

    fun subscribeTopic(topic : String ) {
        try {
            client!!.subscribe(topic, 0, null, object : IMqttActionListener {

                override fun onSuccess(asyncActionToken: IMqttToken?) {
                    Log.i("TAggggG", "subscribed succeed");
                }

                override fun onFailure(asyncActionToken: IMqttToken?, exception: Throwable?) {
                    Log.i("TAggggG", "subscribed failed");
                }
            })
        }
        catch (e : MqttException) {
        }
    }
}