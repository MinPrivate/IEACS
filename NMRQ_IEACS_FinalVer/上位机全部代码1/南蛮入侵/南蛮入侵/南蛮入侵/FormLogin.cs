/***********************************************************************
 *  文件名称：FormLogin.cs
 *  以下代码主要实现FormLogin界面的各类按钮响应及各类信息的显示，
 *  主要实现用户登录功能。
 *  作者：姜玲颖，林雨根。
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
    public partial class FormLogin : Form
    {
        String PC_UserID = "123456";　//用户名默认值赋值
        String PC_Password = "123456";//登陆密码默认值赋值
        public FormLogin()
        {
            InitializeComponent();
        }
        /********************************************************************
         * 函数名:PC_LoginBtn_Click
         * 说明:点击登陆按钮提交用户名及登陆密码，验证信息通过则跳转
         * 主界面，否则弹出错误提示框
         * ******************************************************************/
        private void PC_LoginBtn_Click(object sender, EventArgs e)
        {
            //转移焦点，是选中框不停留在控件上
            this.pictureBox1.Focus();
            if (textBox1.Text == PC_UserID && textBox2.Text == PC_Password)
            {
                this.DialogResult = DialogResult.OK;
                this.Close();
            }  

            else
            {
                FormLoginFail form = new FormLoginFail();//将弹出窗口FormLoginFail实例化
                form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form.ShowDialog();//打开窗口
            }
        }

        private void FormLogin_Load(object sender, EventArgs e)
        {
            //控制窗体在屏幕显示的位置
            this.CenterToScreen();
        }
    }
}