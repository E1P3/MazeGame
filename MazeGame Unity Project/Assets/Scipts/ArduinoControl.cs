using System;
using System.IO.Ports;
using System.Threading;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArduinoControl : MonoBehaviour
{

    static SerialPort _serialPort;

    float x, y, z, px, py, pz;

    // Start is called before the first frame update
    void Start()
    {
        _serialPort = new SerialPort();
        _serialPort.PortName = "COM3"; //Set your board COM
        _serialPort.BaudRate = 9600;
        _serialPort.Open();
    }

    // Update is called once per frame
    void Update()
    {

        string data = _serialPort.ReadLine();

        if (data != null)
        {
            data = data.Trim();

            string[] items = data.Split('/');

            if (items.Length > 1)
            {

                try
                {

                    //--- Roll,Pitch in degrees
                    x = float.Parse(items[0]);
                    y = float.Parse(items[1]);
                    z = float.Parse(items[2]);

                }
                catch (FormatException) {

                    Debug.Log("Format fucked up, using old values");
                    x = px;
                    y = py;
                    z = pz;

                }

                px = x; py = y; pz = z;

                Debug.Log(x + " / " + y + " / " + z);

            }
        }

        transform.rotation = Quaternion.Euler(x, -z, y);
    }

}
