/***********************************************************************
 *  文件名称:FormLogout.cs
 *  以下代码实现用户按关闭按钮显示的提示框。
 *  作者：姜玲颖。
 *  时间：2013年8月1日。
 * ********************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace 南蛮入侵
{
    public partial class FormLogout : Form
    {
        public FormLogout()
        {
            InitializeComponent();
        }
        /********************************************************************
         * 函数名:UI_LogoutBtn_Click
         * 说明:点击确定退出提示,并退出系统
         * ******************************************************************/
        private void UI_LogoutBtn_Click(object sender, EventArgs e)
        {
            //转移焦点，是选中框不停留在控件上
            this.label1.Focus();
            Environment.Exit(1);

        }
        /********************************************************************
         * 函数名:UI_LogoutCancelBtn_Click
         * 说明:点击取消提示,并返回主界面
         * ******************************************************************/
        private void UI_LogoutCancelBtn_Click(object sender, EventArgs e)
        {
            //转移焦点，是选中框不停留在控件上
            this.pictureBox1.Focus();
            //关闭提示窗体
            this.Close();
        }

        private void FormLogout_Load(object sender, EventArgs e)
        {
            //使窗体加载时焦点在label上，去掉button上的焦点框
            this.label1.Select();
            this.label1.Focus();
            //控制窗体在屏幕显示的位置
            this.CenterToScreen();

        }
         
  
     

  

        
    }
}