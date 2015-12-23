/***********************************************************************
 *  文件名称：FormUI.cs
 *  以下代码主要实现FormUI界面的各类按钮响应及各类信息的显示，
 *  包括各类按钮实现的发送串口通讯信息，以及接收串口通讯信息。
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
using System.IO;
using System.IO.Ports;

namespace 南蛮入侵
{
    public partial class FormUI : Form
    {
        int PC_Year, PC_Month, PC_Day, PC_Hour, PC_Minute, PC_Second = 0;  //手动输入年月日时分赋值
        int PC_AcSetHour, PC_AcSetMinute;  //输入空调定时时分赋值
        int PC_WhSetHour, PC_WhSetMinute;  //输入热水器定时时分赋值
        int PC_DlSetHour, PC_DlSetMinute;  //输入门灯定时时分赋值
        int PC_RlSetHour, PC_RlSetMinute;  //输入卧室灯定时时分赋值
        int PC_AcTempSet, PC_WhTempSet;    //输入空调热水器温度设定赋值
        int PC_DataLen; //接收的数据长度
        int PC_ComAcSetHour, PC_ComAcSetMinute, PC_ComWhSetHour, PC_ComWhSetMinute, PC_ComDlSetHour, PC_ComDlSetMinute, PC_ComRlSetHour, PC_ComRlSetMinute, PC_ComSetTemp; //接收到各电器的定时时分,温度
        byte[] PC_Data; //接收的数据
        string PC_StrData; //接收的数据转换为字符串
        string PC_StrDate1, PC_StrDate2, PC_StrDate3, PC_StrDate4; //截取接收的数据的第1,2个,第3,4个,第5,6个,第7,8个字符.
        string PC_Str;     //接受的串口字符串
        DateTime PC_Datetime;  //手动输入日期时间转化的时间格式
        DateTime PC_AcTest;    //手动输入空调定时的时间格式
        DateTime PC_WhTest;    //手动输入热水器定时的时间格式
        DateTime PC_RlTest;    //手动输入卧室灯定时的时间格式
        DateTime PC_DlTest;    //手动输入卧室灯定时的时间格式    
        int PC_AcTimeSet = 0;//空调定时是否启动
        int PC_WhTimeSet = 0;//热水器定时是否启动
        int PC_RlTimeSet = 0;//卧室灯定时是否启动
        int PC_DlTimeSet = 0;//门灯定时是否启动
        int PC_AcOnOff = 2; //空调开关标志
        int PC_WhOnOff = 2; //热水器开关标志
        int PC_DlOnOff = 2; //门灯开关标志
        int PC_RlOnOff = 2; //卧室灯开关标志
        int PC_ComAcSetTag = 2;  //接收到的空调定时标志
        int PC_ComWhSetTag = 2;  //接收到的热水器定时标志
        int PC_ComDlSetTag = 2;  //接收到的门灯定时标志
        int PC_ComRlSetTag = 2;  //接收到的卧室灯定时标志
        bool PC_IsReceving = false;//串口数据接收是否打开
        bool PC_DoingStr = false;//串口数据是否处理
        bool PC_Connect = false  ;//是否连接下位机的标志

        
        public FormUI()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;

        }

        /********************************************************************
         * 函数名:PC_FormUI_Load
         * 说明:进入主界面执行的函数
         * ******************************************************************/
        private void PC_FormUI_Load(object sender, EventArgs e)
        {
            //控制窗体在屏幕显示的位置
            this.CenterToScreen();
            BindPort();
            UI_AcSetTimeComboBox.SelectedIndex = 0;
            UI_WhSetTimeListBox.SelectedIndex = 0;
            UI_DlSetTimeListBox.SelectedIndex = 0;
            UI_RlSetTimeListBox.SelectedIndex = 0;

            if (!serialport.IsOpen)
            {
                PC_OpenPort();
            }
            //发送文本。
            try
            {

                serialport.Write("a000000000000");
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message, "串口调试助手");
            }

        }

        /********************************************************************
         * 函数名:UI_AirConditionBtn_Click
         * 说明:点击空调图标切换到空调设置界面
         * ******************************************************************/
        private void UI_AirConditionBtn_Click(object sender, EventArgs e)
        {
            //转移焦点，使选中框不停留在控件上
            this.label1.Focus();
            //点击空调图标切换到空调设置界面
            this.tabControl1.SelectedIndex = 1;
            this.tabControl2.SelectedIndex = 0;

        }


        /********************************************************************
        * 函数名:UI_DoorLightBtn_Click
        * 说明: 点击门灯图标切换到门灯设置界面
        * ******************************************************************/
        private void UI_DoorLightBtn_Click(object sender, EventArgs e)
        {
            //转移焦点，使选中框不停留在控件上
            this.label1.Focus();
            //点击门灯图标切换到门灯设置界面
            this.tabControl1.SelectedIndex = 1;
            this.tabControl2.SelectedIndex = 2;

        }


        /********************************************************************
        * 函数名:UI_WaterHeaterBtn_Click
        * 说明:点击热水器图标切换到热水器设置界面
        * ******************************************************************/
        private void UI_WaterHeaterBtn_Click(object sender, EventArgs e)
        {
            //转移焦点，使选中框不停留在控件上
            this.label1.Focus();
            //点击热水器图标切换到热水器设置界面
            this.tabControl1.SelectedIndex = 1;
            this.tabControl2.SelectedIndex = 1;
        }


        /********************************************************************
        * 函数名:UI_RoomLightBtn_Click
        * 说明:点击卧室灯图标切换到卧室灯设置界面
        * ******************************************************************/
        private void UI_RoomLightBtn_Click(object sender, EventArgs e)
        {
            //转移焦点，使选中框不停留在控件上
            this.label1.Focus();
            //点击卧室灯图标切换到卧室灯设置界面
            this.tabControl1.SelectedIndex = 1;
            this.tabControl2.SelectedIndex = 3;
        }


        /********************************************************************
        * 函数名:PC_buttonUpdate_Click
        * 说明:状态更新按钮响应
        * ******************************************************************/
        private void PC_buttonUpdate_Click(object sender, EventArgs e)
        {
            //转移焦点，使选中框不停留在控件上
            this.label1.Focus();
            //自动打开串口。
            if (!serialport.IsOpen)
            {
                PC_OpenPort();
            }
            //发送文本。
            try
            {

                serialport.Write("c000000000000");
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message, "串口调试助手");
            }
        }


       
        /********************************************************************
        * 函数名:PC_timer1_Tick
        * 说明:主界面日期时间的显示
        * ******************************************************************/
        private void PC_timer1_Tick(object sender, EventArgs e)
        {
            labelTime.Text = DateTime.Now.ToShortTimeString();
            labelDate.Text = DateTime.Now.ToShortDateString();
            labelWeek.Text = DateTime.Now.ToString("dddd");
            
        //    if (AcTimeSet)
         //   {
          //      if (DateTime.Now.Hour == AcTest.Hour && DateTime.Now.Minute == AcTest.Minute)
          //      {
          //          UI_AirconditionState.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
 
          //      }
         //   }
            
            
        }



        /********************************************************************
        * 函数名:PC_DateTimeSetBtn_Click
        * 说明:设定自定义的时间按钮,按钮获取输入时间日期的值转换成int
        * 并检查输入是否合法,弹出提示信息
        * ******************************************************************/
        private void PC_DateTimeSetBtn_Click(object sender, EventArgs e)
        {
            this.label26.Focus();//转移焦点，使选中框不停留在控件上
            timer1.Enabled = false;
            timer2.Enabled = true;
            int.TryParse(UI_SetYear.Text, out PC_Year);
            int.TryParse(UI_SetMonth.Text, out PC_Month);
            int.TryParse(UI_SetDay.Text, out PC_Day);
            int.TryParse(UI_SetHour.Text, out PC_Hour);
            int.TryParse(UI_SetMinute.Text, out PC_Minute);
            
            try
            {
                PC_Datetime = new DateTime(PC_Year, PC_Month, PC_Day, PC_Hour, PC_Minute, PC_Second);
                FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
            　　form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
            　　form1.ShowDialog();//打开窗口
            }
            catch (Exception ex)
            {
                //弹出输入有误提示框
                FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form.ShowDialog();//打开窗口
            }
            
            
        }


        
        /********************************************************************
        * 函数名:PC_timer2_Tick
        * 说明:用于自设时间在主界面的显示
        * ******************************************************************/
        private void PC_timer2_Tick(object sender, EventArgs e)
        {
            

                PC_Datetime = PC_Datetime.AddSeconds(1);
                labelTime.Text = PC_Datetime.ToShortTimeString();
                labelDate.Text = PC_Datetime.ToShortDateString();
                labelWeek.Text = PC_Datetime.ToString("dddd");
              
            
        }



        /********************************************************************
        * 函数名:PC_tabControl1_Selected
        * 说明:跳转到时间设定界面时各输入框自动获取主界面时间
        * ******************************************************************/
        private void PC_tabControl1_Selected(object sender, TabControlEventArgs e)
        {
            if (timer1.Enabled == true)
            {
                UI_SetYear.Text = DateTime.Now.Year.ToString();
                UI_SetMonth.Text = DateTime.Now.Month.ToString();
                UI_SetDay.Text = DateTime.Now.Day.ToString();
                UI_SetHour.Text = DateTime.Now.Hour.ToString();
                UI_SetMinute.Text = DateTime.Now.Minute.ToString();
            }
            else
            {
                UI_SetYear.Text = PC_Datetime.Year.ToString();
                UI_SetMonth.Text = PC_Datetime.Month.ToString();
                UI_SetDay.Text = PC_Datetime.Day.ToString();
                UI_SetHour.Text = PC_Datetime.Hour.ToString();
                UI_SetMinute.Text = PC_Datetime.Minute.ToString();
            }

        }


        /********************************************************************
        * 函数名:PC_AirConditionBtn_Click
        * 说明:空调开关按钮响应
        * ******************************************************************/
        private void PC_AirConditionBtn_Click(object sender, EventArgs e)
        {
          　
            this.label7.Focus(); //转移焦点，使选中框不停留在控件上
          　if (PC_Connect == true)
            {


                //自动打开串口。
                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    if (PC_AcOnOff == 0)
                    {
                        
                        PC_AcOn();
                       
                        serialport.Write("h100000000000");
                    }
                    else if (PC_AcOnOff == 1)
                    {
                        PC_AcOff();
                        serialport.Write("h000000000000");
                    }

                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }



        /********************************************************************
        * 函数名:PC_FormUI_FormClosing
        * 说明:点击主界面关闭按钮时弹出退出系统窗体
        * ******************************************************************/
        private void PC_FormUI_FormClosing(object sender, FormClosingEventArgs e)
        {
            // 取消关闭窗体    
            e.Cancel = true;
            FormLogout form = new FormLogout();//将弹出窗口FormLogout实例化
            form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
            form.ShowDialog();//打开窗口
          
            
        }



        /********************************************************************
        * 函数名:FormUI_Resize
        * 说明:单击最小化按钮程序最下化到托盘
        * ******************************************************************/
        private void PC_FormUI_Resize(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
              
                this.Hide();
                this.notifyIcon1.Icon = this.Icon;
            }

        }



        /********************************************************************
        * 函数名:PC_notifyIcon1_MouseDoubleClick
        * 说明:双击托盘下图标恢复主界面
        * ******************************************************************/
        private void PC_notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Show();
          
            this.WindowState = FormWindowState.Normal;

           
        }

        
      
        /********************************************************************
       * 函数名:PC_ShowToolStripMenuItem_Click
       * 说明:程序最小化到托盘右键点击“显示”，主界面可见。
       * ******************************************************************/
        private void PC_ShowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Show();

            this.WindowState = FormWindowState.Normal;

        }


        
        /********************************************************************
       * 函数名:PC_ExitToolStripMenuItem_Click
       * 说明:程序最小化到托盘右键点击“退出”，主程序退出
       * ******************************************************************/
        private void PC_ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Environment.Exit(1);
        }
        
      //  private void UI_AirconditionState_Click(object sender, EventArgs e)
     //   {

           
      //  }



        /********************************************************************
       * 函数名:PC_AcTimeSetBtn_Click
       * 说明:空调定时设定确定按钮,并提示是否成功
       * ******************************************************************/
        private void PC_AcTimeSetBtn_Click(object sender, EventArgs e)
        {
            this.label7.Focus();//转移焦点，使选中框不停留在控件上
            
                if (PC_Connect == true)
                {
                    if (UI_AcTimeSetHour.Text == "" || UI_AcTimeSetMinute.Text == "")
                    {
                        FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                        form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                        form.ShowDialog();//打开窗口
                    }
                    else
                    {
                        try
                        {
                            int.TryParse(UI_AcTimeSetHour.Text, out PC_AcSetHour);
                            int.TryParse(UI_AcTimeSetMinute.Text, out PC_AcSetMinute);

                            PC_AcTest = new DateTime(1, 1, 1, PC_AcSetHour, PC_AcSetMinute, 0);



                            //自动打开串口。
                            if (!serialport.IsOpen)
                            {
                                PC_OpenPort();
                            }
                            //发送文本。
                            try
                            {
                                //string PC_AcSetTimeOnOff = UI_DlSetTimeListBox.SelectedItem.ToString();
                                if (UI_AcSetTimeComboBox.SelectedItem.ToString() == "开")
                                {

                                    PC_AcTimeSet = 11;
                                    PC_AcTimer.Enabled = true;

                                    serialport.Write("j" + PC_AcTest.ToString("HHmm") + "10000000");
                                }
                                else if (UI_AcSetTimeComboBox.SelectedItem.ToString() == "关")
                                {
                                    PC_AcTimeSet = 10;
                                    PC_AcTimer.Enabled = true;
                                    serialport.Write("j" + PC_AcTest.ToString("HHmm") + "00000000");
                                }

                            }
                            catch (Exception err)
                            {
                                MessageBox.Show(err.Message, "串口调试助手");
                            }



                            //弹出设定成功提示框
                            FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                            form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                            form1.ShowDialog();//打开窗口
                        }
                        catch (Exception ex)
                        {
                            //弹出输入有误提示框
                            FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                            form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                            form.ShowDialog();//打开窗口
                        }
                    }
                }
                else
                {
                    PC_ShowUnconnectForm();
                }
            }
        

        /********************************************************************
       * 函数名:PC_WhTimeSetBtn_Click
       * 说明:热水器定时设定确定按钮,并提示是否成功
       * ******************************************************************/
        private void PC_WhTimeSetBtn_Click(object sender, EventArgs e)
        {
            this.label12.Focus();//转移焦点，使选中框不停留在控件上
            //转移焦点，使选中框不停留在控件上
            this.label15.Focus();
            if (PC_Connect == true)
            {
                if (UI_WhTimeSetHour.Text == "" || UI_WhTimeSetMinute.Text == "")
                {
                    FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                    form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                    form.ShowDialog();//打开窗口
                }
                else
                {
                    try
                    {
                        int.TryParse(UI_WhTimeSetHour.Text, out PC_WhSetHour);
                        int.TryParse(UI_WhTimeSetMinute.Text, out PC_WhSetMinute);
                        PC_WhTest = new DateTime(1, 1, 1, PC_WhSetHour, PC_WhSetMinute, 0);



                        //自动打开串口。
                        if (!serialport.IsOpen)
                        {
                            PC_OpenPort();
                        }
                        //发送文本。
                        try
                        {
                            if (UI_WhSetTimeListBox.SelectedItem.ToString() == "开")
                            {
                                PC_WhTimeSet = 11;
                                PC_WhTimer.Enabled = true;
                                serialport.Write("m" + PC_WhTest.ToString("HHmm") + "10000000");
                            }
                            if (UI_WhSetTimeListBox.SelectedItem.ToString() == "关")
                            {
                                PC_WhTimeSet = 10;
                                PC_WhTimer.Enabled = true;
                                serialport.Write("m" + PC_WhTest.ToString("HHmm") + "00000000");
                            }

                            // serialport.Write(EncodeByte, 0, Len);
                        }
                        catch (Exception err)
                        {
                            MessageBox.Show(err.Message, "串口调试助手");
                        }



                        //弹出设定成功提示框
                        FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                        form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                        form1.ShowDialog();//打开窗口

                    }
                    catch (Exception ex)
                    {
                        //弹出输入有误提示框
                        FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                        form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                        form.ShowDialog();//打开窗口
                    }
                }
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }


        /********************************************************************
       * 函数名:PC_DlTimeSetBtn_Click
       * 说明:热水器定时设定确定按钮,并提示是否成功
       * ******************************************************************/
        private void PC_DlTimeSetBtn_Click(object sender, EventArgs e)
        {
            this.label19.Focus();//转移焦点，使选中框不停留在控件上
            //转移焦点，使选中框不停留在控件上
            //  this.label15.Focus();
            if (PC_Connect == true)
            {
                if (UI_DlTimeSetHour.Text == "" || UI_DlTimeSetMinute.Text == "")
                {
                    FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                    form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                    form.ShowDialog();//打开窗口
                }
                else
                {
                    try
                    {
                        int.TryParse(UI_DlTimeSetHour.Text, out PC_DlSetHour);
                        int.TryParse(UI_DlTimeSetMinute.Text, out PC_DlSetMinute);
                        PC_DlTest = new DateTime(1, 1, 1, PC_DlSetHour, PC_DlSetMinute, 0);



                        //自动打开串口。
                        if (!serialport.IsOpen)
                        {
                            PC_OpenPort();
                        }
                        //发送文本。
                        try
                        {

                            if (UI_DlSetTimeListBox.SelectedItem.ToString() == "开")
                            {
                                PC_DlTimeSet = 11;
                                PC_DlTimer.Enabled = true;
                                serialport.Write("e" + PC_DlTest.ToString("HHmm") + "10000000");
                            }
                            if (UI_DlSetTimeListBox.SelectedItem.ToString() == "关")
                            {
                                PC_DlTimeSet = 10;
                                PC_DlTimer.Enabled = true;
                                serialport.Write("e" + PC_DlTest.ToString("HHmm") + "00000000");
                            }
                        }
                        catch (Exception err)
                        {
                            MessageBox.Show(err.Message, "串口调试助手");
                        }



                        //弹出设定成功提示框
                        FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                        form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                        form1.ShowDialog();//打开窗口

                    }
                    catch (Exception ex)
                    {
                        //弹出输入有误提示框
                        FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                        form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                        form.ShowDialog();//打开窗口
                    }
                }
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }
        /********************************************************************
       * 函数名:PC_RlTimeSetBtn_Click
       * 说明:热水器定时设定确定按钮,并提示是否成功
       * ******************************************************************/
        private void PC_RlTimeSetBtn_Click(object sender, EventArgs e)
        {
            this.label22.Focus();//转移焦点，使选中框不停留在控件上
            if (PC_Connect == true)
            {
                if (UI_RlTimeSetHour.Text == "" || UI_RlTimeSetMinute.Text == "")
                {
                    FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                    form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                    form.ShowDialog();//打开窗口
                }
                else
                {
                    try
                    {
                        int.TryParse(UI_RlTimeSetHour.Text, out PC_RlSetHour);
                        int.TryParse(UI_RlTimeSetMinute.Text, out PC_RlSetMinute);
                        PC_RlTest = new DateTime(1, 1, 1, PC_RlSetHour, PC_RlSetMinute, 0);



                        //自动打开串口。
                        if (!serialport.IsOpen)
                        {
                            PC_OpenPort();
                        }
                        //发送文本。
                        try
                        {

                            if (UI_RlSetTimeListBox.SelectedItem.ToString() == "开")
                            {
                                PC_RlTimeSet = 11;
                                PC_RlTimer.Enabled = true;
                                serialport.Write("m" + PC_RlTest.ToString("HHmm") + "10000000");
                            }
                            if (UI_RlSetTimeListBox.SelectedItem.ToString() == "关")
                            {
                                PC_RlTimeSet = 10;
                                PC_RlTimer.Enabled = true;
                                serialport.Write("m" + PC_RlTest.ToString("HHmm") + "00000000");
                            };
                        }
                        catch (Exception err)
                        {
                            MessageBox.Show(err.Message, "串口调试助手");
                        }





                        //弹出设定成功提示框
                        FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                        form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                        form1.ShowDialog();//打开窗口
                    }
                    catch (Exception ex)
                    {
                        //弹出输入有误提示框
                        FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                        form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                        form.ShowDialog();//打开窗口
                    }
                }
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }


        /********************************************************************
       * 函数名:以下各类XXX_KeyPress
       * 说明:各类输入关于日期时间的只能为数字
       * ******************************************************************/
        /*****************************************************************************************/

         private void UI_SetYear_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void UI_SetMonth_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void UI_SetDay_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void UI_SetHour_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;
        }

        private void UI_SetMinute_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void UI_RlTimeSetHour_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void UI_RlTimeSetMinute_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void textBox6_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void UI_WhTimeSetHour_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void UI_WhTimeSetMinute_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void textBox3_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void UI_AcTimeSetHour_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }

        private void UI_AcTimeSetMinute_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && (e.KeyChar != 8) && (e.KeyChar != 46))
                e.Handled = true;

        }
      
      /*****************************************************************************************/


        /********************************************************************
       * 函数名:PC_AcTempSetBtn_Click
       * 说明:空调温度设定按钮,并提示是否成功
       * ******************************************************************/
        private void PC_AcTempSetBtn_Click(object sender, EventArgs e)
        {
           this.label7.Focus();//转移焦点，使选中框不停留在控件上

            int.TryParse(UI_AcTempSet.Text, out PC_AcTempSet);
            if (PC_Connect == true)
            {

                if (PC_AcTempSet > 32 || PC_AcTempSet < 16)
                {
                    //显示输入有误
                    FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                    form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                    form.ShowDialog();//打开窗口
                }
                else
                {
                    
                    //自动打开串口。
                    if (!serialport.IsOpen)
                    {
                        PC_OpenPort();
                    }
                    //发送文本。
                    try
                    {
                        UI_AcSetTempInfo.Text = PC_AcTempSet.ToString() + "℃";
                        UI_labelAcTemp.Text = PC_AcTempSet.ToString() + "℃";
                        serialport.Write("i" + UI_AcTempSet.Text + "0000000000");
                    }
                    catch (Exception err)
                    {
                        MessageBox.Show(err.Message, "串口调试助手");
                    }




                    //显示设定成功
                    FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                    form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                    form1.ShowDialog();//打开窗口
                }
            }
            else
            {
                PC_ShowUnconnectForm();
            }
           }
        
        /********************************************************************
      * 函数名:PC_AcTimeCancelBtn_Click
      * 说明:空调定时取消按钮,并提示是否成功
      * ******************************************************************/
        private void PC_AcTimeCancelBtn_Click(object sender, EventArgs e)
        {
            this.label7.Focus();//转移焦点，使选中框不停留在控件上
            //自动打开串口。
            if (PC_Connect == true)
            {
                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    PC_AcTimeSetCancel();
                    serialport.Write("j000000000000");
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }



                //显示设定成功
                FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form1.ShowDialog();//打开窗口
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }


        /********************************************************************
        * 函数名:PC_WhTempSetBtn_Click
        * 说明:点击热水器温度设定按钮响应,并提示是否成功
        * ******************************************************************/
        private void PC_WhTempSetBtn_Click(object sender, EventArgs e)
        {
            this.label12.Focus();//转移焦点，使选中框不停留在控件上
            int.TryParse(UI_WhTempSet.Text, out PC_WhTempSet);
            if (PC_Connect == true)
            {
                if (PC_WhTempSet > 70 || PC_WhTempSet < 30)
                {
                    // 显示输入有误
                    FormWrongInput form = new FormWrongInput();//将弹出窗口FormWrongDate实例化
                    form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                    form.ShowDialog();//打开窗口
                }
                else
                {
                    
                    //自动打开串口。
                    if (!serialport.IsOpen)
                    {
                        PC_OpenPort();
                    }
                    //发送文本。
                    try
                    {
                        UI_labelWhTemp.Text = PC_WhTempSet.ToString() + "℃";
                        UI_WhSetTempInfo.Text = PC_WhTempSet.ToString() + "℃";
                        serialport.Write("l" + UI_WhTempSet + "0000000000");
                    }
                    catch (Exception err)
                    {
                        MessageBox.Show(err.Message, "串口调试助手");
                    }




                    //显示设定成功
                    FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                    form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                    form1.ShowDialog();//打开窗口
                }
            }
            else
            {
                PC_ShowUnconnectForm();
            }

        }


        /********************************************************************
         * 函数名:PC_WhTimeCancelBtn_Click
         * 说明:点击热水器定时取消按钮响应,并提示是否成功
         * ******************************************************************/
        private void PC_WhTimeCancelBtn_Click(object sender, EventArgs e)
        {
            this.label12.Focus();//转移焦点，使选中框不停留在控件上
            if (PC_Connect == true)
            {
                //自动打开串口。
                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    PC_WhTimeSetCancel();
                    serialport.Write("m000000000000");
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }



                //显示设定成功
                FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form1.ShowDialog();//打开窗口
            }
            else
            {
                PC_ShowUnconnectForm();
            }
    }



        /********************************************************************
      * 函数名:PC_DlTimeCancelBtn_Click
      * 说明:点击门灯定时取消按钮响应,并提示是否成功
      * ******************************************************************/
        private void PC_DlTimeCancelBtn_Click(object sender, EventArgs e)
        {
            this.label18.Focus();//转移焦点，使选中框不停留在控件上
            if (PC_Connect == true)
            {
                //自动打开串口。
                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    PC_DlTimeSetCancel();
                    serialport.Write("e000000000000");
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }

                //显示设定成功
                FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form1.ShowDialog();//打开窗口
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }

        /********************************************************************
      * 函数名:PC_RlTimeCancelBtn_Click
      * 说明:点击卧室灯定时取消按钮响应,并提示是否成功
      * ******************************************************************/
        private void PC_RlTimeCancelBtn_Click(object sender, EventArgs e)
        {
            this.label22.Focus();//转移焦点，使选中框不停留在控件上
           
            if (PC_Connect == true)
            {
                //自动打开串口。
                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    PC_RlTimeSetCancel();
                    serialport.Write("g000000000000");
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }



                //显示设定成功
                FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form1.ShowDialog();//打开窗口
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }



        /********************************************************************
      * 函数名:BindPort
      * 说明:自动获取串行口名称
      * ******************************************************************/
        private void BindPort()
        {
            try
            {
                //自动获取串行口名称
                foreach (string port in SerialPort.GetPortNames())
                {
                  //  this.cbxPort.Items.Add(port);
                }
               // cbxPort.SelectedIndex = 0;
            }
            catch
            {
                MessageBox.Show("找不到通讯串口！", "串口调试助手");
            }
        }



        /********************************************************************
      * 函数名:PC_serialPort_DataReceived
      * 说明:串口接收数据函数
      * ******************************************************************/
        private void PC_serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                //***正在接收状态指示。
                PC_IsReceving = true;
                //读入收到的数据。
                int Len = serialport.BytesToRead;
                if (Len < 1)
                {
                    //***接收完成状态指示。
                    PC_IsReceving = false;
                    return;
                }

                byte[] data = new byte[Len];
                serialport.Read(data, 0, Len);
                
                //字符串处理。
                 PC_Str = Encoding.GetEncoding("GB2312").GetString(data);

                 PC_Unshow.Invoke(new EventHandler(delegate
                    {
                        //***正在处理字符串。
                        PC_DoingStr = true;
                        PC_Unshow.AppendText(PC_Str);
                       

                        //***完成处理字符串。
                        PC_DoingStr = false;
                    }
                    )); 
                  while (PC_DoingStr)
                   {
                       //处理串口接收事件及其它系统消息。
                       Application.DoEvents();
                   }
                /*
                //使用委托跨线程读取数据。
                 
                   UI_AcTempSet.Invoke(new EventHandler(delegate
                   {
                       //***正在处理字符串。
                       PC_DoingStr = true;

                       UI_AcTempSet.AppendText(Str);
     
                       //***完成处理字符串。
                       PC_DoingStr = false;
                   }
                   )); 

                

                   while (PC_DoingStr)
                   {
                       //处理串口接收事件及其它系统消息。
                       Application.DoEvents();
                   }*/
                   //***接收完成状态指示。
                 
               }
            
            catch (Exception Err)
            {
                MessageBox.Show(Err.Message, "串口调试助手");
            }


            PC_ComProcess();


        
            
        }



        /********************************************************************
      * 函数名:PC_SendTimeBtn_Click
      * 说明:与下位机同步时间按钮响应
      * ******************************************************************/
        private void PC_SendTimeBtn_Click(object sender, EventArgs e)
        {
            this.label26.Focus();//转移焦点，使选中框不停留在控件上
            //自动打开串口。
            if (!serialport.IsOpen)
            {
                PC_OpenPort();
            }
            //发送文本。
            try
            {
                if (timer1.Enabled == true)
                {
                    serialport.Write("o" + DateTime.Now.ToString("yyyyMMddHHmm"));
                }
                if (timer2.Enabled == true)
                {
                    serialport.Write("o" + PC_Datetime.ToString("yyyyMMddHHmm"));
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message, "串口调试助手");
            }
        }



        /********************************************************************
      * 函数名:PC_OpenPort()
      * 说明:打开串口函数
      * ******************************************************************/
        private void PC_OpenPort()
        {
            //***避免串口死锁***
            //写超时，如果底层串口驱动效率问题，能有效的避免死锁。
            serialport.WriteTimeout = 1000;
            //读超时，同上。
            serialport.ReadTimeout = 1000;
            //回车换行。
            serialport.NewLine = "\r\n";
            //注册事件。
            serialport.DataReceived += new SerialDataReceivedEventHandler(this.PC_serialPort_DataReceived);
            //***避免串口死锁***
            
              serialport.PortName = "COM1";
              serialport.BaudRate = int.Parse("9600");
              serialport.DataBits = int.Parse("8");
              serialport.Parity = (Parity)Enum.Parse(typeof(Parity),"None");
              serialport.StopBits = (StopBits)Enum.Parse(typeof(StopBits),"One");
              serialport.Open();
        }




        /********************************************************************
      * 函数名:PC_WaterHeaterBtn_Click
      * 说明:热水器开关按钮响应
      * ******************************************************************/
        private void PC_WaterHeaterBtn_Click(object sender, EventArgs e)
        {
            this.label12.Focus();//转移焦点，使选中框不停留在控件上
            if (PC_Connect == true)
            {

                //自动打开串口。
                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    if (PC_WhOnOff == 0)
                    {
                        PC_WhOn();
                        serialport.Write("k100000000000");
                    }
                    else if (PC_WhOnOff == 1)
                    {
                        PC_WhOff();
                        serialport.Write("k000000000000");
                    }
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }




        /********************************************************************
      * 函数名:PC_DoorLightBtn_Click
      * 说明:门灯开关按钮响应
      * ******************************************************************/
        private void PC_DoorLightBtn_Click(object sender, EventArgs e)
        {
            this.label18.Focus();//转移焦点，使选中框不停留在控件上
            //自动打开串口。
            if (!serialport.IsOpen)
            {
                PC_OpenPort();
            }
            //发送文本。
            try
            {
                if (PC_DlOnOff == 0)
                {
                    PC_DlOn();
                    serialport.Write("d100000000000");
                }
                else if (PC_DlOnOff == 1)
                {
                    PC_DlOff();
                    serialport.Write("d000000000000");
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message, "串口调试助手");
            }
        }




        /********************************************************************
      * 函数名:PC_RoomLightBtn_Click
      * 说明:卧室灯开关按钮响应
      * ******************************************************************/
        private void PC_RoomLightBtn_Click(object sender, EventArgs e)
        {
            this.label22.Focus();//转移焦点，使选中框不停留在控件上
            //自动打开串口。
            if (!serialport.IsOpen)
            {
                PC_OpenPort();
            }
            //发送文本。
            try
            {
                if (PC_RlOnOff == 0)
                {
                    PC_RlOn();
                    serialport.Write("f100000000000");
                }
                else if (PC_RlOnOff == 1)
                {
                    PC_RlOff();
                    serialport.Write("f000000000000");
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message, "串口调试助手");
            }
        }



        /********************************************************************
      * 函数名:PC_NormalMode_Click
      * 说明:选中普通模式响应
      * ******************************************************************/
        private void PC_NormalMode_Click(object sender, EventArgs e)
        {
            if (PC_Connect == true)
            {
                //自动打开串口。

                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    UI_labelMode.Text = "普通模式";
                    serialport.Write("n000000000000");
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }
                FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form1.ShowDialog();//打开窗口
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }


        /********************************************************************
      * 函数名:PC_GoHomeMode_Click
      * 说明:选中回家模式响应
      * ******************************************************************/
        private void PC_GoHomeMode_Click(object sender, EventArgs e)
        {
            if (PC_Connect == true)
            {
                //自动打开串口。

                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    PC_AcOn();
                    PC_WhOn();
                    PC_DlOn();
                    UI_labelMode.Text = "回家模式";
                    serialport.Write("n100000000000");
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }

                FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form1.ShowDialog();//打开窗口
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }



        /********************************************************************
      * 函数名:PC_OutMode_Click
      * 说明:选中外出模式响应
      * ******************************************************************/
        private void PC_OutMode_Click(object sender, EventArgs e)
        {
            if (PC_Connect == true)
            {
                //自动打开串口。
                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    PC_AcOff();
                    PC_WhOff();
                    PC_DlOff();
                    PC_RlOff();
                    UI_labelMode.Text = "外出模式";
                    serialport.Write("n200000000000");
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }


                FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form1.ShowDialog();//打开窗口
            }

            else
            {
                PC_ShowUnconnectForm();
            }
        }



        /********************************************************************
      * 函数名: PC_AntiThiefMode_Click
      * 说明:选中防盗模式响应
      * ******************************************************************/
        private void PC_AntiThiefMode_Click(object sender, EventArgs e)
        {
            if (PC_Connect == true)
            {
                //自动打开串口。
                if (!serialport.IsOpen)
                {
                    PC_OpenPort();
                }
                //发送文本。
                try
                {
                    UI_labelMode.Text = "防盗模式";
                    serialport.Write("n300000000000");
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.Message, "串口调试助手");
                }

                FormSuccess form1 = new FormSuccess();//将弹出窗口FormSuccess实例化
                form1.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
                form1.ShowDialog();//打开窗口
            }
            else
            {
                PC_ShowUnconnectForm();
            }
        }

        /********************************************************************
 * 函数名:PC_AcOn
 * 说明:空调开函数
 * ******************************************************************/
        private void PC_AcOn()
        {
            UI_AirconditionState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
            UI_AirconditionState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
            PC_AcOnOff = 1;
        }

        /********************************************************************
 * 函数名:PC_AcOff
 * 说明:空调关函数
 * ******************************************************************/
        private void PC_AcOff()
        {
            UI_AirconditionState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
            UI_AirconditionState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
            PC_AcOnOff = 0;
        }

        /********************************************************************
 * 函数名:PC_WhOn
 * 说明:热水器开函数
 * ******************************************************************/
        private void PC_WhOn()
        {
            UI_WaterheaterState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
            UI_WaterheaterState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
            PC_WhOnOff = 1;
        }

        /********************************************************************
 * 函数名:PC_WhOff
 * 说明:热水器关函数
 * ******************************************************************/
        private void PC_WhOff()
        {
            UI_WaterheaterState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
            UI_WaterheaterState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
            PC_WhOnOff = 0;
        }

        /********************************************************************
 * 函数名:PC_DlOn
 * 说明:门灯开函数
 * ******************************************************************/
        private void PC_DlOn()
        {
            UI_DoorlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
            UI_DoorlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
            PC_DlOnOff = 1;
        }


        /********************************************************************
 * 函数名:PC_DlOff
 * 说明:门灯关函数
 * ******************************************************************/
        private void PC_DlOff()
        {
            UI_DoorlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
            UI_DoorlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
            PC_DlOnOff = 0;
        }


        /********************************************************************
 * 函数名:PC_RlOn
 * 说明:卧室灯开函数
 * ******************************************************************/
        private void PC_RlOn()
        {
            UI_RoomlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
            UI_RoomlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
            PC_RlOnOff = 1;
        }


        /********************************************************************
 * 函数名:PC_RlOff
 * 说明:卧室灯关函数
 * ******************************************************************/
        private void PC_RlOff()
        {
            UI_RoomlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
            UI_RoomlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
            PC_RlOnOff = 0;
        }


        /********************************************************************
  * 函数名:PC_AcTimeSetCancel
  * 说明:空调定时取消响应
  * ******************************************************************/
        private void PC_AcTimeSetCancel()
        {
            PC_AcTimer.Enabled = false;
            PC_AcTimeSet = 0;
            UI_AcSetTimeInfo.Text = "　　无定时";
            UI_labelAcInfo.Text = "　　无定时";
        }

        /********************************************************************
* 函数名:PC_WhTimeSetCancel
* 说明:热水器定时取消响应
* ******************************************************************/
        private void PC_WhTimeSetCancel()
        {
            PC_WhTimer.Enabled = false;
            PC_WhTimeSet = 0;
            UI_WhSetTimeInfo.Text = "　　无定时";
            UI_labelWhInfo.Text = "　　无定时";
        }


        /********************************************************************
   * 函数名:PC_DlTimeSetCancel
   * 说明:门灯定时取消响应
   * ******************************************************************/
        private void PC_DlTimeSetCancel()
        {
            PC_DlTimer.Enabled = false;
            PC_DlTimeSet = 0;
            UI_DlSetTimeInfo.Text = "　　无定时";
            UI_labelDlInfo.Text = "　　无定时";
        }


        /********************************************************************
* 函数名:PC_RlTimeSetCancel
* 说明:卧室灯定时取消响应
* ******************************************************************/
        private void PC_RlTimeSetCancel()
        {
            PC_RlTimer.Enabled = false;
            PC_RlTimeSet = 0;
            UI_RlSetTimeInfo.Text = "　　无定时";
            UI_labelRlInfo.Text = "　　无定时";
        }


   /********************************************************************
  * 函数名:PC_ComProcess()
  * 说明:处理接收到的字符串
  * ******************************************************************/
        private void PC_ComProcess()
        {
            if (PC_Unshow.Text.Length == 13)
            {
                PC_StrData = PC_Unshow.Text.ToString();                
                PC_InfoProcess();
                PC_Unshow.Text = "";
            }
        }

  /********************************************************************
  * 函数名:PC_InfoProcess
  * 说明:下位机发上来的信息处理
  * ******************************************************************/
        private void PC_InfoProcess()
        {
            
            string S1, S2, S3, S4;
            S1 = PC_StrData;
            S2 = PC_StrData;
            S3 = PC_StrData;
            S4 = PC_StrData;



            PC_StrDate1 = S1.Substring(0, 1);
            PC_StrDate2 = S2.Substring(1, 2);
            PC_StrDate3 = S3.Substring(3, 2);
            PC_StrDate4 = S4.Substring(5, 1);

           

            if (PC_StrData.ToString() == "d100000000000") //门灯开
            {
                PC_DlOn();
            }
            else if (PC_StrData.ToString() == "d000000000000") //门灯关
            {
                PC_DlOff();
            }



            else if (PC_StrData.ToString() == "h100000000000") //空调开
            {
                PC_AcOn();
            }
            else if (PC_StrData.ToString() == "h000000000000") //空调关
            {
                PC_AcOff();
            }


            else if (PC_StrData.ToString() == "k100000000000") //热水器开
            {
                PC_WhOn();
            }
            else if (PC_StrData.ToString() == "k000000000000") //热水器关
            {
                PC_WhOff();
            }



            else if (PC_StrData.ToString() == "f100000000000") //卧室灯开
            {
                PC_RlOn();
            }
            else if (PC_StrData.ToString() == "f000000000000") //卧室灯关
            {
                PC_RlOff();
            }

            else if (PC_StrData.ToString() == "r000000000000") //小偷警报
            {
                UI_Alarm.Text = "小偷进入";
                UI_PoliceState.BackgroundImage =　南蛮入侵.Properties.Resources.红灯;

            }
            else if (PC_StrData.ToString() == "s000000000000") //煤气警报
            {
                //煤气警报事件
                UI_Alarm.Text = "煤气泄漏";
                UI_PoliceState.BackgroundImage = 南蛮入侵.Properties.Resources.红灯;
            }
           else if (PC_StrData.ToString() == "t000000000000") //一切正常
            {
                //一切正常事件
                UI_Alarm.Text = "一切正常";
                UI_PoliceState.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
            }
            else if (PC_StrData.ToString() == "n000000000000") //普通模式
            {
                //普通模式事件
                UI_labelMode.Text = "普通模式";
            }
            else if (PC_StrData == "n100000000000") //回家模式
            {
                //回家模式事件
                PC_AcOn();
                PC_DlOn();
                PC_WhOn();
                UI_labelMode.Text = "回家模式";
            }
            else if (PC_StrData.ToString() == "n300000000000") //防盗模式
            {
                //防盗模式事件
                UI_labelMode.Text = "防盗模式";
            }
            else if (PC_StrData == "n200000000000") //外出模式
            {
                //外出模式事件
                PC_AcOff();
                PC_WhOff();
                PC_DlOff();
                PC_RlOff();
                
                UI_labelMode.Text = "外出模式";

            }
            else if (PC_StrData.ToString() == "b000000000000") //显示已与下位机连接
            {
                //显示已连接
                UI_labelConnect.Text = "已连接到下位机";
                PC_Connect = true;
            }
            else if (PC_StrData.ToString() == "z000000000000") //下位机关闭
            {
                UI_labelConnect.Text = "未连接到下位机";
                PC_Connect = false;
            }

            else if (PC_StrData.ToString() == "e000000000000") //门灯定时取消
            {
                this.Invoke(new MethodInvoker(PC_DlTimer.Stop));
                PC_DlTimeSet = 0;
                UI_DlSetTimeInfo.Text = "　　无定时";
                UI_labelDlInfo.Text = "　　无定时";
            }
            else if (PC_StrData.ToString() == "g000000000000") //卧室灯定时取消
            {
                this.Invoke(new MethodInvoker(PC_RlTimer.Stop));
                PC_RlTimeSet = 0;
                UI_RlSetTimeInfo.Text = "　　无定时";
                UI_labelRlInfo.Text = "　　无定时";
                
            }
            else if (PC_StrData.ToString() == "j000000000000") //空调定时取消
            {
                this.Invoke(new MethodInvoker(PC_AcTimer.Stop));
                PC_AcTimeSet = 0;
                UI_AcSetTimeInfo.Text = "　　无定时";
                UI_labelAcInfo.Text = "　　无定时";


            }
            else if (PC_StrData.ToString() == "m000000000000") //热水器定时取消
            {
                this.Invoke(new MethodInvoker(PC_WhTimer.Stop));
                PC_WhTimeSet = 0;
                UI_WhSetTimeInfo.Text = "　　无定时";
                UI_labelWhInfo.Text = "　　无定时";
            }
        
            else
            {
                
               if (PC_StrDate1 == "g")  //卧室灯定时
                {
                    int.TryParse(PC_StrDate2, out PC_ComRlSetHour);
                    int.TryParse(PC_StrDate3, out PC_ComRlSetMinute);
                    PC_RlTest = new DateTime(1, 1, 1, PC_ComRlSetHour, PC_ComRlSetMinute, 0);


                    if (PC_StrDate4 == "1")
                    {
                        //卧室灯定时开事件
                        PC_RlTimeSet = 11;
                        this.Invoke(new MethodInvoker(PC_RlTimer.Start));
                        UI_RlSetTimeInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "开启";
                        UI_labelRlInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "开启";

                    }
                    if (PC_StrDate4 == "0")
                    {
                        //卧室灯定时关闭事件
                        PC_RlTimeSet = 10;
                        this.Invoke(new MethodInvoker(PC_RlTimer.Start));
                        UI_RlSetTimeInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "关闭";
                        UI_labelRlInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "关闭";
                    }
                }
                if (PC_StrDate1 == "m") //热水器定时
                {
                    int.TryParse(PC_StrDate2, out PC_ComWhSetHour);
                    int.TryParse(PC_StrDate3, out PC_ComWhSetMinute);
                    PC_WhTest = new DateTime(1, 1, 1, PC_ComWhSetHour, PC_ComWhSetMinute, 0);

                    if (PC_StrDate4 == "1")
                    {
                        //热水器定时开事件
                        PC_WhTimeSet = 11;
                        this.Invoke(new MethodInvoker(PC_WhTimer.Start));
                        UI_WhSetTimeInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "开启";
                        UI_labelWhInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "开启";
                    }
                    if (PC_StrDate4 == "0")
                    {
                        //热水器定时关闭事件
                        PC_WhTimeSet = 10;
                        this.Invoke(new MethodInvoker(PC_WhTimer.Start));
                        UI_WhSetTimeInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "关闭";
                        UI_labelWhInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "关闭";
                        
                    }
                }
                if (PC_StrDate1 == "j") //空调定时
                {

                    int.TryParse(PC_StrDate2, out PC_ComAcSetHour);
                    int.TryParse(PC_StrDate3, out PC_ComAcSetMinute);
                    PC_AcTest = new DateTime(1, 1, 1, PC_ComAcSetHour, PC_ComAcSetMinute, 0);
                   

                    PC_AcTest = new DateTime(1, 1, 1, PC_AcSetHour, PC_AcSetMinute, 0);

                    if (PC_StrDate4 == "1")
                    {
                        //空调定时开事件
                        PC_AcTimeSet = 11;
                        this.Invoke(new MethodInvoker(PC_AcTimer.Start));
                      
                        UI_AcSetTimeInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "开启";
                        UI_labelAcInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "开启";
                    }
                    if (PC_StrDate4 == "0")
                    {
                        //空调定时关闭事件
                        PC_AcTimeSet = 10;

                        this.Invoke(new MethodInvoker(PC_AcTimer.Start));
                        
                        UI_AcSetTimeInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "关闭";
                        UI_labelAcInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "关闭";
                      
                    }
                }
                if (PC_StrDate1 == "e") //门灯定时
                {

                    int.TryParse(PC_StrDate2, out PC_ComDlSetHour);
                    int.TryParse(PC_StrDate3, out PC_ComDlSetMinute);
                    PC_DlTest = new DateTime(1, 1, 1, PC_ComDlSetHour, PC_ComDlSetMinute, 0);


                    if (PC_StrDate4 == "1")
                    {
                        //门灯定时开事件
                        PC_DlTimeSet = 11;
                        this.Invoke(new MethodInvoker(PC_DlTimer.Start));
                        UI_DlSetTimeInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "开启";
                        UI_labelDlInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "开启";
                    }
                    if (PC_StrDate4 == "0")
                    {
                        //门灯定时关闭事件
                        PC_DlTimeSet = 10;
                        this.Invoke(new MethodInvoker(PC_DlTimer.Start));
                        UI_DlSetTimeInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "关闭";
                        UI_labelDlInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "关闭";
                    }
                }
                if (PC_StrDate1 == "i") //空调温度设定事件
                {
                    int.TryParse(PC_StrDate2, out PC_ComSetTemp);

                    //空调温度设定事件
                    UI_AcSetTempInfo.Text = PC_ComSetTemp.ToString() + "℃";
                    UI_labelAcTemp.Text = PC_ComSetTemp.ToString() + "℃";


                }

                if (PC_StrDate1 == "l") //热水器温度设定事件
                {
                    int.TryParse(PC_StrDate2, out PC_ComSetTemp);
                    //热水器温度设定事件

                    UI_labelWhTemp.Text = PC_ComSetTemp.ToString() + "℃";
                    UI_WhSetTempInfo.Text = PC_ComSetTemp.ToString() + "℃";
                }
               
            }




        }



        /********************************************************************
        * 函数名:PC_AcTimer_Tick
        * 说明:空调定时开关操作
        * ******************************************************************/
        private void PC_AcTimer_Tick(object sender, EventArgs e)
        {
           
            if (timer1.Enabled == true)
            {

                if (PC_AcTimeSet == 11) 
                {
                    UI_AcSetTimeInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "开启";
                    UI_labelAcInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "开启";
                    if (DateTime.Now.Hour == PC_AcTest.Hour && DateTime.Now.Minute == PC_AcTest.Minute)
                    {
                        UI_AirconditionState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        UI_AirconditionState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        
                        PC_AcTimeSet = 0;
                        PC_AcOnOff = 1;
                        UI_AcSetTimeInfo.Text = "　　无定时";
                        UI_labelAcInfo.Text = "　　无定时";
                        PC_AcTimer.Enabled = false;
                    }
                }
                if (PC_AcTimeSet == 10)
                {
                    UI_AcSetTimeInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "关闭";
                    UI_labelAcInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "关闭";

                    if (DateTime.Now.Hour == PC_AcTest.Hour && DateTime.Now.Minute == PC_AcTest.Minute)
                    {
                        UI_AirconditionState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        UI_AirconditionState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        
                        PC_AcTimeSet = 0;
                        PC_AcOnOff = 0;
                        UI_AcSetTimeInfo.Text = "　　无定时";
                        UI_labelAcInfo.Text = "　　无定时";
                        PC_AcTimer.Enabled = false;
                    }

                }
            }
            else
            {
                if (PC_AcTimeSet == 11)
                {
                    UI_AcSetTimeInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "开启";
                    UI_labelAcInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "开启";
                    if (PC_Datetime.Hour == PC_AcTest.Hour && PC_Datetime.Minute == PC_AcTest.Minute)
                    {
                        UI_AirconditionState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        UI_AirconditionState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        
                        PC_AcTimeSet = 0;
                        PC_AcOnOff = 1;
                        UI_AcSetTimeInfo.Text = "　　无定时";
                        UI_labelAcInfo.Text = "　　无定时";
                        PC_AcTimer.Enabled = false;
                    }
                }
                if (PC_AcTimeSet == 10)
                {
                    UI_AcSetTimeInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "关闭";
                    UI_labelAcInfo.Text = "空调将于" + PC_AcTest.ToShortTimeString() + "关闭";
                    if (PC_Datetime.Hour == PC_AcTest.Hour && PC_Datetime.Minute == PC_AcTest.Minute)
                    {
                        UI_AirconditionState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        UI_AirconditionState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                       
                        PC_AcTimeSet = 0;
                        PC_AcOnOff = 0;
                        UI_AcSetTimeInfo.Text = "　　无定时";
                        UI_labelAcInfo.Text = "　　无定时";
                        PC_AcTimer.Enabled = false;
                    }

                }
            }
             
        }



        /********************************************************************
      * 函数名:PC_WhTimer_Tick
      * 说明:热水器定时开关操作
      * ******************************************************************/
        private void PC_WhTimer_Tick(object sender, EventArgs e)
        {
            if (timer1.Enabled == true)
            {
                if (PC_WhTimeSet == 11)
                {
                    UI_WhSetTimeInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "开启";
                    UI_labelWhInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "开启";
                    if (DateTime.Now.Hour == PC_WhTest.Hour && DateTime.Now.Minute == PC_WhTest.Minute)
                    {
                        UI_WaterheaterState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        UI_WaterheaterState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        
                        PC_WhTimeSet = 0;
                        PC_WhOnOff = 1;
                        UI_WhSetTimeInfo.Text = "　　无定时";
                        UI_labelWhInfo.Text = "　　无定时";
                        PC_WhTimer.Enabled = false;
                    }
                }
                if (PC_WhTimeSet == 10)
                {
                    UI_WhSetTimeInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "关闭";
                    UI_labelWhInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "关闭";
                    if (DateTime.Now.Hour == PC_WhTest.Hour && DateTime.Now.Minute == PC_WhTest.Minute)
                    {
                        UI_WaterheaterState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        UI_WaterheaterState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        
                        PC_WhTimeSet = 0;
                        PC_WhOnOff = 0;
                        UI_WhSetTimeInfo.Text = "　　无定时";
                        UI_labelWhInfo.Text = "　　无定时";
                        PC_WhTimer.Enabled = false;
                    }

                }
            }
            else
            {
                if (PC_WhTimeSet == 11)
                {
                    UI_WhSetTimeInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "开启";
                    UI_labelWhInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "开启";
                    if (PC_Datetime.Hour == PC_WhTest.Hour && PC_Datetime.Minute  == PC_WhTest.Minute)
                    {
                        UI_WaterheaterState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        UI_WaterheaterState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        
                        PC_WhTimeSet = 0;
                        PC_WhOnOff = 1;
                        UI_WhSetTimeInfo.Text = "　　无定时";
                        UI_labelWhInfo.Text = "　　无定时";
                        PC_WhTimer.Enabled = false;
                    }
                }
                if (PC_WhTimeSet == 10)
                {
                    UI_WhSetTimeInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "关闭";
                    UI_labelWhInfo.Text = "热水器将于" + PC_WhTest.ToShortTimeString() + "关闭";
                    if (PC_Datetime.Hour == PC_WhTest.Hour && PC_Datetime.Minute == PC_WhTest.Minute)
                    {
                        UI_WaterheaterState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        UI_WaterheaterState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                       
                        PC_WhTimeSet = 0;
                        PC_WhOnOff = 0;
                        UI_WhSetTimeInfo.Text = "　　无定时";
                        UI_labelWhInfo.Text = "　　无定时";
                        PC_WhTimer.Enabled = false;
                    }

                }
            }
        }




     /********************************************************************
      * 函数名:PC_DlTimer_Tick
      * 说明:门灯定时开关操作
      * ******************************************************************/
        private void PC_DlTimer_Tick(object sender, EventArgs e)
        {
            if (timer1.Enabled == true)
            {
                if (PC_DlTimeSet == 11)
                {
                    UI_DlSetTimeInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "开启";
                    UI_labelDlInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "开启";
                    if (DateTime.Now.Hour == PC_DlTest.Hour && DateTime.Now.Minute == PC_DlTest.Minute)
                    {
                        UI_DoorlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        UI_DoorlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                     
                        PC_DlTimeSet = 0;
                        PC_DlOnOff = 1;
                        UI_DlSetTimeInfo.Text = "　　无定时";
                        UI_labelDlInfo.Text = "　　无定时";
                        PC_DlTimer.Enabled = false;
                    }
                }
                if (PC_DlTimeSet == 10)
                {
                    UI_DlSetTimeInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "关闭";
                    UI_labelDlInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "关闭";
                    if (DateTime.Now.Hour == PC_DlTest.Hour && DateTime.Now.Minute == PC_DlTest.Minute)
                    {
                        UI_DoorlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        UI_DoorlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        
                        PC_DlTimeSet = 0;
                        PC_DlOnOff = 0;
                        UI_DlSetTimeInfo.Text = "　　无定时";
                        UI_labelDlInfo.Text = "　　无定时";
                        PC_DlTimer.Enabled = false;
                    }

                }
            }
            else
            {
                if (PC_DlTimeSet == 11)
                {
                    UI_DlSetTimeInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "开启";
                    UI_labelDlInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "开启";
                    if (PC_Datetime.Hour == PC_DlTest.Hour && PC_Datetime.Minute == PC_DlTest.Minute)
                    {
                        UI_DoorlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        UI_DoorlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                       
                        PC_DlTimeSet = 0;
                        PC_DlOnOff = 1;
                        UI_DlSetTimeInfo.Text = "　　无定时";
                        UI_labelDlInfo.Text = "　　无定时";
                        PC_DlTimer.Enabled = false;
                    }
                }
                if (PC_DlTimeSet == 10)
                {
                    UI_DlSetTimeInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "关闭";
                    UI_labelDlInfo.Text = "门灯将于" + PC_DlTest.ToShortTimeString() + "关闭";
                    if (PC_Datetime.Hour == PC_DlTest.Hour && PC_Datetime.Minute == PC_DlTest.Minute)
                    {
                        UI_DoorlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        UI_DoorlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        
                        PC_DlTimeSet = 0;
                        PC_DlOnOff = 0;
                        UI_DlSetTimeInfo.Text = "　　无定时";
                        UI_labelDlInfo.Text = "　　无定时";
                        PC_DlTimer.Enabled = false;
                    }

                }
            }
        }




        /********************************************************************
        * 函数名:PC_RlTimer_Tick
        * 说明:卧室灯灯定时开关操作
        * ******************************************************************/
        private void PC_RlTimer_Tick(object sender, EventArgs e)
        {
            if (timer1.Enabled == true)
            {
                if (PC_RlTimeSet == 11)
                {
                    UI_RlSetTimeInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "开启";
                    UI_labelRlInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "开启";
                    if (DateTime.Now.Hour  == PC_RlTest.Hour && DateTime.Now.Minute == PC_RlTest.Minute)
                    {
                        UI_RoomlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        UI_RoomlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        
                        PC_RlTimeSet = 0;
                        PC_RlOnOff = 1;
                        UI_RlSetTimeInfo.Text = "　　无定时";
                        UI_labelRlInfo.Text = "　　无定时";
                        PC_RlTimer.Enabled = false;
                    }
                }
                if (PC_RlTimeSet == 10)  
                {
                    UI_RlSetTimeInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "关闭";
                    UI_labelRlInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "关闭";
                    if (DateTime.Now.Hour == PC_RlTest.Hour && DateTime.Now.Minute == PC_RlTest.Minute)
                    {
                        UI_RoomlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        UI_RoomlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        
                        PC_RlTimeSet = 0;
                        PC_RlOnOff = 0;
                        UI_RlSetTimeInfo.Text = "　　无定时";
                        UI_labelRlInfo.Text = "　　无定时";
                        PC_RlTimer.Enabled = false;
                    }

                }
            }
            else
            {
                if (PC_RlTimeSet == 11)
                {
                    UI_RlSetTimeInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "开启";
                    UI_labelRlInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "开启";
                    if (PC_Datetime.Hour == PC_RlTest.Hour && PC_Datetime.Minute == PC_RlTest.Minute)
                    {
                        UI_RoomlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        UI_RoomlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.绿灯;
                        
                        PC_RlTimeSet = 0;
                        PC_RlOnOff = 1;
                        UI_RlSetTimeInfo.Text = "　　无定时";
                        UI_labelRlInfo.Text = "　　无定时";
                        PC_RlTimer.Enabled = false;
                    }
                }
                if (PC_RlTimeSet == 10)
                {
                    UI_RlSetTimeInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "关闭";
                    UI_labelRlInfo.Text = "卧室灯将于" + PC_RlTest.ToShortTimeString() + "关闭";
                    if (PC_Datetime.Hour == PC_RlTest.Hour && PC_Datetime.Minute == PC_RlTest.Minute)
                    {
                        UI_RoomlightState1.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                        UI_RoomlightState2.BackgroundImage = 南蛮入侵.Properties.Resources.灰灯;
                       
                        PC_RlTimeSet = 0;
                        PC_RlOnOff = 0;
                        UI_RlSetTimeInfo.Text = "　　无定时";
                        UI_labelRlInfo.Text = "　　无定时";
                        PC_RlTimer.Enabled = false;
                    }

                }
            }
        }

        private void PC_ShowUnconnectForm()
        {
            //空调设置界面如果本地控制中则弹出提示框
            FormInvalid form = new FormInvalid();//将弹出窗口FormInvalid实例化
            form.Visible = false;//将当前窗口设置为不可视；如果不这样处理则系统报错。
            form.ShowDialog();//打开窗口
        }

        /********************************************************************
       * 函数名:UI_AirconditionState1_Click
       * 说明:主界面空调开关操作
       * ******************************************************************/
        private void UI_AirconditionState1_Click(object sender, EventArgs e)
        {
            PC_AirConditionBtn_Click(null, null);
        }


        /********************************************************************
      * 函数名:UUI_DoorlightState1_Click
      * 说明:主界面空调开关操作
      * ******************************************************************/
        private void UI_DoorlightState1_Click(object sender, EventArgs e)
        {
            PC_DoorLightBtn_Click(null, null);
        }


        /********************************************************************
      * 函数名:UI_WaterheaterState1_Click
      * 说明:主界面空调开关操作
      * ******************************************************************/
        private void UI_WaterheaterState1_Click(object sender, EventArgs e)
        {
            PC_WaterHeaterBtn_Click(null, null);
        }


        /********************************************************************
      * 函数名:UI_RoomlightState1_Click
      * 说明:主界面空调开关操作
      * ******************************************************************/
        private void UI_RoomlightState1_Click(object sender, EventArgs e)
        {
            PC_RoomLightBtn_Click(null, null);
        }

       
       

       
       
       
        
    }
}