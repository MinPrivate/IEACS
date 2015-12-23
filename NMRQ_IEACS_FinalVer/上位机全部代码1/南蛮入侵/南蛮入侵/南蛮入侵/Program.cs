using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace 南蛮入侵
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            FormLogin form = new FormLogin();
            if (form.ShowDialog() == DialogResult.OK)
            {
                Application.Run(new FormUI());
            }
            else
            {
                Application.Exit();
            }
        }
    }
}