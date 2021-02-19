using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using ROBOTIS;
using System.Net;
using System.Net.Sockets;

namespace Send_Recieve
{
    class Program
    {
        // Defulat setting
        public const int DEFAULT_PORTNUM = 6; // COM3
        public const int TIMEOUT_TIME = 1000; // msec

        static void Main(string[] args)
        {
            int startkey = 0;
            Socket sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPEndPoint ep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 7000);
            sock.Bind(ep);
            sock.Listen(10);
            Socket clientSock = sock.Accept();
            int e = 0;
            //byte[] buff = new byte[10];
            string data = null;
            string d = null;
            int result = 0;
            while (true)
            {
                byte[] buff = new byte[10];
                int n = clientSock.Receive(buff);
                //Console.WriteLine(data);
                //Console.WriteLine(buff[0]);
                //Console.WriteLine(buff[1]);

                data = Encoding.Default.GetString(buff, 0, n);
                //Console.WriteLine(data);
                if (data == "1")
                {
                    //Console.WriteLine("1");
                    startkey = 1;
                    e = 1;
                }
                else if (data == "hi")
                {
                    //Console.WriteLine("2");
                    startkey = 2;
                    e = 1;  
                }
                else if (data == "nm")
                {
                    Console.WriteLine("nm");
                    startkey = 3;
                    e = 1;
                }
                else if (data == "bath")
                {
                    Console.WriteLine("bath");
                    startkey = 4;
                    e = 1;
                }

                else if (data == "tempo")
                {
                    Console.WriteLine("tempo");
                    startkey = 5;
                    e = 1;
                }
                else if (data == "count")
                {
                    Console.WriteLine("count");
                    startkey = 6;
                    e = 1;
                }
                else if (data == "great")
                {
                    Console.WriteLine("great");
                    startkey = 7;
                    e = 1;
                }
                else if (data == "hello")
                {
                    Console.WriteLine("hello");
                    startkey = 8;
                    e = 1;
                }
                //d = "hi";
                //byte[] msg = Encoding.Default.GetBytes(d);
                //clientSock.Send(msg, SocketFlags.None);
                int TxData = -1, RxData = -1;
                
                if (e == 1)
                {
                    if (zigbee.zgb_initialize(DEFAULT_PORTNUM) == 0)
                    {
                        Console.WriteLine("Failed to open Zig2Serial!");
                        Console.WriteLine("Press any key to terminate...");
                        Console.ReadKey(true);
                        return;
                    }
                    else
                    {
                        Console.WriteLine(startkey);

                        TxData = zigbee.RC100_BTN_4;
                        if (startkey == 1)
                        {
                            TxData = zigbee.RC100_BTN_U;
                        }
                        if (startkey == 2)
                        {
                            TxData = zigbee.RC100_BTN_D;

                        }
                        if (startkey == 3)
                        {
                            TxData = zigbee.RC100_BTN_5;
                        }
                        if (startkey == 4)
                        {
                            TxData = zigbee.RC100_BTN_4;
                        }

                        if (startkey == 5)
                        {
                            TxData = zigbee.RC100_BTN_6;
                        }
                        if (startkey == 6)
                        {
                            TxData = zigbee.RC100_BTN_3;
                        }
                        if (startkey == 7)
                        {
                            TxData = zigbee.RC100_BTN_2;
                        }
                        if (startkey == 8)
                        {
                            TxData = zigbee.RC100_BTN_2;
                        }
                        if (zigbee.zgb_tx_data(TxData) == 1)
                        {
                            Console.WriteLine("succeed");
                            e = 0;
                            if (startkey == 2)
                            {
                                while (result < 2000)
                                {
                                    TxData = zigbee.RC100_BTN_D;
                                    zigbee.zgb_tx_data(TxData);
                                    Console.WriteLine(result);
                                    result++;
                                }
                                result = 0;
                                startkey = 0;
                            }
                            /*
                            Console.WriteLine(zigbee.zgb_rx_check());
                            if (zigbee.zgb_rx_check() == 1)
                            {
                                // Get data verified
                                if (zigbee.zgb_rx_data() == 1)
                                {
                                    e = 0;
                                }
                                RxData = zigbee.zgb_rx_data();
                                Console.WriteLine("Recieved: {0:d}", RxData);
                                break;
                            }
                            else
                            {
                                Console.WriteLine("fail2");
                            }
                            */
                        }
                        else

                        {
                            Console.WriteLine("fail");
                        }
                    }
                }

            }
        }
    }
}
