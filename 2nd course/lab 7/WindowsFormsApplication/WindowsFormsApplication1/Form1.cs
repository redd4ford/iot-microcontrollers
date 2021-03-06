using System;
using System.Data;
using System.Linq;
using System.Windows.Forms;
using System.IO.Ports;
using System.Collections.Generic;
using System.Text;

namespace WindowsFormsApplication1 {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }
        
        private void comboBox1_Click(object sender, EventArgs e) {
            int num;
            comboBox1.Items.Clear();
            string[] ports = SerialPort
                .GetPortNames()
                .OrderBy(a => 
                    a.Length > 3 
                    && int.TryParse(a.Substring(3),
                        out num
                    )
                ? num : 0)
                .ToArray();
            comboBox1.Items.AddRange(ports);
        }

        private void buttonOpenPort_Click(object sender, EventArgs e) {
            if (!serialPort1.IsOpen) {
                try {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.Open();
                    buttonOpenPort.Text = "Закрити";
                    comboBox1.Enabled = false;
                    buttonFromSlave1.Visible = true;
                    buttonFromSlave2.Visible = true;
                } catch {
                    MessageBox.Show("Порт невалідний: " + comboBox1.Text, "ПОМИЛКА", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            } else {
                serialPort1.Close();
                buttonOpenPort.Text = "Відкрити";
                comboBox1.Enabled = true;
                buttonFromSlave1.Visible = false;
                buttonFromSlave2.Visible = false;
            }
        }

        private void buttonFromSlave1_Click(object sender, EventArgs e) {
            byte[] b1 = new byte[3];
            b1[0] = 0x7B; // SLAVE 1 ADDRESS
            b1[1] = 0xB1;
            serialPort1.Write(b1, 0, 2);
            TextBox[] myArr = { textBox1 };
       
            textBox1.Clear();
                List<string> charsList = new List<string>();
                List<byte> byteList = new List<byte>();
                List<byte> reflectedByteList = new List<byte>();
                List<byte> checkSumList = new List<byte>();

                for (int i = 0; i < 7; i++)
                {
                    byte info = (byte)serialPort1.ReadByte();
                    Console.WriteLine(info);
                    byteList.Add(info);
                    switch (info)
                    {
                        case 0x1A:
                            charsList.Add("1");
                            break;

                        case 0x2A:
                            charsList.Add("2");
                            break;

                        case 0x3A:
                            charsList.Add("3");
                            break;

                        case 0x4A:
                            charsList.Add("4");
                            break;

                        case 0x5A:
                            charsList.Add("5");
                            break;

                        case 0x6A:
                            charsList.Add("6");
                            break;

                        case 0x7A:
                            charsList.Add("7");
                            break;

                        case 0x8A:
                            charsList.Add("8");
                            break;

                        case 0x9A:
                            charsList.Add("9");
                            break;

                        case 0x0A:
                            charsList.Add("0");
                            break;

                        case 0xFF:
                            charsList.Add(".");
                            break;

                        default:
                            charsList.Add("");
                            break;
                    };

                if (i == 5)
                {
                    byteList.Remove(info);
                    checkSumList.Add(info);
                }
                if (i == 6)
                {
                    byteList.Remove(info);
                    checkSumList.Add(info);
                }

            }
                StringBuilder builder = new StringBuilder();
                foreach (string character in charsList)
                {
                    builder.Append(character);
                }

            byte[] bytes = byteList.ToArray();
            byte[] checkSumbytes = checkSumList.ToArray();

            ushort checkSumValue = (ushort)CombineBytes(checkSumbytes[0], checkSumbytes[1]);

            foreach (byte b in bytes)
            {
                byte reflectedByte = ReverseByte(b);
                reflectedByteList.Add(reflectedByte);
            }
            byte[] reflectedBytes = reflectedByteList.ToArray();

            ushort resultCheckSum = Compute_CRC8(reflectedBytes);

            string result = builder.ToString();
            Console.WriteLine(result.ToString());
 
            if (checkSumValue == resultCheckSum)
            {
                myArr[0].Text = result.ToString();

            }
            else
            {
                myArr[0].Text = result.ToString() + " (" + checkSumValue.ToString() + " / " + resultCheckSum.ToString() + ")";
            }
     
        }

        private void buttonFromSlave2_Click(object sender, EventArgs e) {
            textBox2.Clear();
            byte[] b1 = new byte[3];
            b1[0] = 0xEA; // SLAVE 2 ADDRESS
            b1[1] = 0xB1;
            serialPort1.Write(b1, 0, 2);
            TextBox[] myArr = { textBox2};
       
                List<string> numberList = new List<string>();
                List<byte> byteList = new List<byte>();
                List<byte> reflectedByteList = new List<byte>();
                List<byte> checkSumList = new List<byte>();
                for (int i = 0; i < 7; i++)
                {
                    byte info = (byte)serialPort1.ReadByte();
                    byteList.Add(info);
                    switch (info)
                    {
                        case 0x0A:
                            numberList.Add("0");
                            break;

                        case 0x1A:
                            numberList.Add("1");
                            break;

                        case 0x2A:
                            numberList.Add("2");
                            break;

                        case 0x3A:
                            numberList.Add("3");
                            break;

                        case 0x4A:
                            numberList.Add("4");
                            break;

                        case 0x5A:
                            numberList.Add("5");
                            break;

                        case 0x6A:
                            numberList.Add("6");
                            break;

                        case 0x7A:
                            numberList.Add("7");
                            break;

                        case 0x8A:
                            numberList.Add("8");
                            break;

                        case 0x9A:
                            numberList.Add("9");
                            break;

                        case 0xFF:
                            numberList.Add(".");
                            break;

                        default:
                            numberList.Add("");
                            break;
                    };

                if (i == 5)
                {
                    byteList.Remove(info);
                    checkSumList.Add(info);
                }
                if (i == 6)
                {
                    byteList.Remove(info);
                    checkSumList.Add(info);
                }

            }
                StringBuilder builder = new StringBuilder();
                foreach (string date in numberList)
                {
                    builder.Append(date);
                }

            byte[] bytes = byteList.ToArray();
            byte[] checkSumbytes = checkSumList.ToArray();

            ushort checkSumValue = (ushort)CombineBytes(checkSumbytes[0], checkSumbytes[1]);

            foreach (byte b in bytes)
            {
                byte reflectedByte = ReverseByte(b);
                reflectedByteList.Add(reflectedByte);
            }

            byte[] reflectedBytes = reflectedByteList.ToArray();
            ushort resultCheckSum = Compute_CRC8(reflectedBytes);

            string result = builder.ToString();
            if (checkSumValue == resultCheckSum)
            {
                myArr[0].Text = result.ToString();

            }
            else
            {
                myArr[0].Text = result.ToString() + " (" + checkSumValue.ToString() + " / " + resultCheckSum.ToString() + ")";
            }

        }

        public static ushort Compute_CRC8(byte[] bytes)
        {
            const ushort generator = 0xD5;
            ushort crc = 0x00;

            foreach (byte b in bytes)
            {
                crc ^= (ushort)(b << 8);

                for (int i = 0; i < 8; i++)
                {
                    if ((crc & 0x8000) != 0)
                    {
                        crc = (ushort)((crc << 1) ^ generator);
                    }
                    else
                    {
                        crc <<= 1;
                    }
                }
            }
            ushort myNewResult = Reflect8(crc);
            return myNewResult;
        }

        public static ushort Reflect8(ushort val)
        {
            ushort resVal = 0;

            for (int i = 0; i < 16; i++)
            {
                if ((val & (1 << i)) != 0)
                {
                    resVal |= (ushort)(1 << (15 - i));
                }
            }

            return resVal;
        }

        public static byte ReverseByte(byte b)
        {
            int a = 0;
            for (int i = 0; i < 8; i++)
            {
                if ((b & (1 << i)) != 0)
                {
                    a |= 1 << (7 - i);
                }
            }
            return (byte)a;
        }

        public int CombineBytes(byte b1, byte b2)
        {
            int combined = b1 << 8 | b2;
            return combined;
        }

        private void label1_Click(object sender, EventArgs e)
        {
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
        }
    }
}
