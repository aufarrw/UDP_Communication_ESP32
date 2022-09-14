using System;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace ESP32_UDP_Protocol
{
    public partial class Form1 : Form
    {
        UdpClient udpClient = new UdpClient();
        public Form1()
        {
            InitializeComponent();
        }

        Boolean status = false;
        private void btnConnect_Click(object sender, EventArgs e)
        {
            Thread thdUDPServer = new Thread(new ThreadStart(serverThread));
            IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Any, 8080);

            thdUDPServer.IsBackground = true; //<-- Set the thread to work in background
            thdUDPServer.Start();

            status = true;
            btnConnect.Visible = false;
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            udpClient.Connect(tbIPaddress.Text, Convert.ToInt16(tbPort.Text));
            Byte[] senddata = Encoding.ASCII.GetBytes(tbSend.Text);
            udpClient.Send(senddata, senddata.Length);
        }

        public void serverThread() //SERVER
        {
            UdpClient udpClient = new UdpClient(8080);
            while (status)
            {
                IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Any, 8080);
                Byte[] receiveBytes = udpClient.Receive(ref RemoteIpEndPoint);
                string returnData = Encoding.ASCII.GetString(receiveBytes);

                this.Invoke(new MethodInvoker(delegate ()
                {
                    date = DateTime.Now.ToString("dd:hh:mm:ss;");
                    data = date + returnData;

                    tbIPaddress.Text = RemoteIpEndPoint.Address.ToString();

                    rtbReceive.AppendText(data + "\n");
                    rtbReceive.ScrollToCaret();
                }
                ));
            }
        }

        string data = "";
        string date = "";

        string[] data_str = new string[25];
    }
}