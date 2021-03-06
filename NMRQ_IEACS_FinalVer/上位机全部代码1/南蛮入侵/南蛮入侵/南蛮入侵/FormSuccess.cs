﻿/***********************************************************************
 *  文件名称：FormSuccess.cs
 *  以下代码实现用户按钮操作成功时显示信息。
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
    public partial class FormSuccess : Form
    {
        public FormSuccess()
        {
            InitializeComponent();
        }
        /********************************************************************
         * 函数名:UI_SuccessBtn_Click
         * 说明:点击确定提示，并返回主界面
         * ******************************************************************/
        private void UI_SuccessBtn_Click(object sender, EventArgs e)
        {
            //转移焦点，是选中框不停留在控件上
            this.label1.Focus();
            //关闭提示窗体
            this.Close();
        }

        private void FormSuccess_Load(object sender, EventArgs e)
        {
            //使窗体加载时焦点在label上，去掉button上的焦点框
            this.label1.Select();
            this.label1.Focus();
            //控制窗体在屏幕显示的位置
            this.CenterToScreen();
        }

    }
}