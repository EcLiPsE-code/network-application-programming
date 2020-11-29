using FTPServer.server;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FTPServer
{
    class Program
    {
        static void Main(string[] args)
        {
            FtpServer server = new FtpServer();
            server.Start();

            Console.ReadKey();
        }
    }
}
