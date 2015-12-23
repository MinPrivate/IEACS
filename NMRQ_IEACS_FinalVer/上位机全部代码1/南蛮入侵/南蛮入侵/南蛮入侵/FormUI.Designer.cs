using System.Windows.Forms;

namespace 南蛮入侵
{
    partial class FormUI
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }
        protected override void WndProc(ref Message m)
        {

            if (m.Msg == 0x0014) // 禁掉清除背景消息

                return;

            base.WndProc(ref m);

        }


        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormUI));
            this.skinEngineUI = new Sunisoft.IrisSkin.SkinEngine(((System.ComponentModel.Component)(this)));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPageInfo = new System.Windows.Forms.TabPage();
            this.PC_Unshow = new System.Windows.Forms.TextBox();
            this.UI_labelWhTemp = new System.Windows.Forms.Label();
            this.label38 = new System.Windows.Forms.Label();
            this.UI_labelAcTemp = new System.Windows.Forms.Label();
            this.label37 = new System.Windows.Forms.Label();
            this.UI_labelDlInfo = new System.Windows.Forms.Label();
            this.UI_labelWhInfo = new System.Windows.Forms.Label();
            this.UI_labelRlInfo = new System.Windows.Forms.Label();
            this.UI_labelAcInfo = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.UI_Alarm = new System.Windows.Forms.Label();
            this.UI_PoliceState = new System.Windows.Forms.PictureBox();
            this.UI_RoomlightState1 = new System.Windows.Forms.PictureBox();
            this.UI_WaterheaterState1 = new System.Windows.Forms.PictureBox();
            this.UI_DoorlightState1 = new System.Windows.Forms.PictureBox();
            this.UI_AirconditionState1 = new System.Windows.Forms.PictureBox();
            this.PC_buttonUpdate = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBoxPolic = new System.Windows.Forms.PictureBox();
            this.UI_RoomLightBtn = new System.Windows.Forms.Button();
            this.UI_WaterHeaterBtn = new System.Windows.Forms.Button();
            this.UI_DoorLightBtn = new System.Windows.Forms.Button();
            this.UI_AirConditionBtn = new System.Windows.Forms.Button();
            this.groupBoxData = new System.Windows.Forms.GroupBox();
            this.UI_labelMode = new System.Windows.Forms.Label();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.labelWeek = new System.Windows.Forms.Label();
            this.UI_labelConnect = new System.Windows.Forms.Label();
            this.UI_labelLight = new System.Windows.Forms.Label();
            this.UI_labelTemp = new System.Windows.Forms.Label();
            this.labelDate = new System.Windows.Forms.Label();
            this.labelTime = new System.Windows.Forms.Label();
            this.tabPageControl = new System.Windows.Forms.TabPage();
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.tabPageAir = new System.Windows.Forms.TabPage();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.UI_AcSetTimeComboBox = new System.Windows.Forms.ComboBox();
            this.UI_AcSetTempInfo = new System.Windows.Forms.Label();
            this.label39 = new System.Windows.Forms.Label();
            this.UI_AcSetTimeInfo = new System.Windows.Forms.Label();
            this.label0 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.UI_AcTimeSetHour = new System.Windows.Forms.TextBox();
            this.UI_AcTimeSetMinute = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.UI_AcTempSet = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.UI_AirconditionState2 = new System.Windows.Forms.PictureBox();
            this.PC_AirConditionBtn = new System.Windows.Forms.Button();
            this.PC_AcTempSetBtn = new System.Windows.Forms.Button();
            this.PC_AcTimeCancelBtn = new System.Windows.Forms.Button();
            this.PC_AcTimeSetBtn = new System.Windows.Forms.Button();
            this.tabPageHot = new System.Windows.Forms.TabPage();
            this.pictureBox5 = new System.Windows.Forms.PictureBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.UI_WhSetTimeListBox = new System.Windows.Forms.ComboBox();
            this.UI_WhSetTempInfo = new System.Windows.Forms.Label();
            this.label41 = new System.Windows.Forms.Label();
            this.UI_WhSetTimeInfo = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.UI_WhTimeSetHour = new System.Windows.Forms.TextBox();
            this.UI_WhTimeSetMinute = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.UI_WhTempSet = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.UI_WaterheaterState2 = new System.Windows.Forms.PictureBox();
            this.PC_WaterHeaterBtn = new System.Windows.Forms.Button();
            this.PC_WhTempSetBtn = new System.Windows.Forms.Button();
            this.PC_WhTimeCancelBtn = new System.Windows.Forms.Button();
            this.PC_WhTimeSetBtn = new System.Windows.Forms.Button();
            this.tabPageDoor = new System.Windows.Forms.TabPage();
            this.pictureBox6 = new System.Windows.Forms.PictureBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.UI_DlSetTimeListBox = new System.Windows.Forms.ComboBox();
            this.UI_DlSetTimeInfo = new System.Windows.Forms.Label();
            this.PC_DoorLightBtn = new System.Windows.Forms.Button();
            this.UI_DoorlightState2 = new System.Windows.Forms.PictureBox();
            this.label20 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.UI_DlTimeSetHour = new System.Windows.Forms.TextBox();
            this.UI_DlTimeSetMinute = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.PC_DlTimeCancelBtn = new System.Windows.Forms.Button();
            this.PC_DlTimeSetBtn = new System.Windows.Forms.Button();
            this.tabPageBed = new System.Windows.Forms.TabPage();
            this.pictureBox7 = new System.Windows.Forms.PictureBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.UI_RlSetTimeListBox = new System.Windows.Forms.ComboBox();
            this.UI_RlSetTimeInfo = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.UI_RlTimeSetHour = new System.Windows.Forms.TextBox();
            this.UI_RlTimeSetMinute = new System.Windows.Forms.TextBox();
            this.label22 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.UI_RoomlightState2 = new System.Windows.Forms.PictureBox();
            this.PC_RoomLightBtn = new System.Windows.Forms.Button();
            this.PC_RlTimeCancelBtn = new System.Windows.Forms.Button();
            this.PC_RlTimeSetBtn = new System.Windows.Forms.Button();
            this.tabPageTime = new System.Windows.Forms.TabPage();
            this.pictureBox8 = new System.Windows.Forms.PictureBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.PC_SendTimeBtn = new System.Windows.Forms.Button();
            this.label32 = new System.Windows.Forms.Label();
            this.label31 = new System.Windows.Forms.Label();
            this.UI_SetMinute = new System.Windows.Forms.TextBox();
            this.UI_SetHour = new System.Windows.Forms.TextBox();
            this.PC_DateTimeSetBtn = new System.Windows.Forms.Button();
            this.label28 = new System.Windows.Forms.Label();
            this.label27 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.UI_SetDay = new System.Windows.Forms.TextBox();
            this.UI_SetMonth = new System.Windows.Forms.TextBox();
            this.UI_SetYear = new System.Windows.Forms.TextBox();
            this.label30 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.tabPageMode = new System.Windows.Forms.TabPage();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.pictureBox12 = new System.Windows.Forms.PictureBox();
            this.pictureBox11 = new System.Windows.Forms.PictureBox();
            this.pictureBox10 = new System.Windows.Forms.PictureBox();
            this.pictureBox9 = new System.Windows.Forms.PictureBox();
            this.label36 = new System.Windows.Forms.Label();
            this.label35 = new System.Windows.Forms.Label();
            this.label34 = new System.Windows.Forms.Label();
            this.label33 = new System.Windows.Forms.Label();
            this.PC_NormalMode = new System.Windows.Forms.RadioButton();
            this.PC_GoHomeMode = new System.Windows.Forms.RadioButton();
            this.PC_OutMode = new System.Windows.Forms.RadioButton();
            this.PC_AntiThiefMode = new System.Windows.Forms.RadioButton();
            this.tabPageHelp = new System.Windows.Forms.TabPage();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.label42 = new System.Windows.Forms.Label();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.label40 = new System.Windows.Forms.Label();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.imageList2 = new System.Windows.Forms.ImageList(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.显示ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.退出ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.serialport = new System.IO.Ports.SerialPort(this.components);
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.PC_DlTimer = new System.Windows.Forms.Timer(this.components);
            this.PC_RlTimer = new System.Windows.Forms.Timer(this.components);
            this.PC_WhTimer = new System.Windows.Forms.Timer(this.components);
            this.PC_AcTimer = new System.Windows.Forms.Timer(this.components);
            this.tabControl1.SuspendLayout();
            this.tabPageInfo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_PoliceState)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.UI_RoomlightState1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.UI_WaterheaterState1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.UI_DoorlightState1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.UI_AirconditionState1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxPolic)).BeginInit();
            this.groupBoxData.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.tabPageControl.SuspendLayout();
            this.tabControl2.SuspendLayout();
            this.tabPageAir.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_AirconditionState2)).BeginInit();
            this.tabPageHot.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_WaterheaterState2)).BeginInit();
            this.tabPageDoor.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox6)).BeginInit();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_DoorlightState2)).BeginInit();
            this.tabPageBed.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox7)).BeginInit();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_RoomlightState2)).BeginInit();
            this.tabPageTime.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox8)).BeginInit();
            this.groupBox5.SuspendLayout();
            this.tabPageMode.SuspendLayout();
            this.groupBox6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox12)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox11)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox10)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox9)).BeginInit();
            this.tabPageHelp.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // skinEngineUI
            // 
            this.skinEngineUI.DisableTag = 0;
            this.skinEngineUI.SerialNumber = "";
            this.skinEngineUI.SkinFile = null;
            this.skinEngineUI.SkinStreamMain = ((System.IO.Stream)(resources.GetObject("skinEngineUI.SkinStreamMain")));
            // 
            // tabControl1
            // 
            this.tabControl1.Alignment = System.Windows.Forms.TabAlignment.Left;
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPageInfo);
            this.tabControl1.Controls.Add(this.tabPageControl);
            this.tabControl1.Controls.Add(this.tabPageTime);
            this.tabControl1.Controls.Add(this.tabPageMode);
            this.tabControl1.Controls.Add(this.tabPageHelp);
            this.tabControl1.ImageList = this.imageList1;
            this.tabControl1.ItemSize = new System.Drawing.Size(20, 25);
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Multiline = true;
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(644, 492);
            this.tabControl1.TabIndex = 0;
            this.tabControl1.Tag = "";
            this.tabControl1.Selected += new System.Windows.Forms.TabControlEventHandler(this.PC_tabControl1_Selected);
            // 
            // tabPageInfo
            // 
            this.tabPageInfo.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("tabPageInfo.BackgroundImage")));
            this.tabPageInfo.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPageInfo.Controls.Add(this.PC_Unshow);
            this.tabPageInfo.Controls.Add(this.UI_labelWhTemp);
            this.tabPageInfo.Controls.Add(this.label38);
            this.tabPageInfo.Controls.Add(this.UI_labelAcTemp);
            this.tabPageInfo.Controls.Add(this.label37);
            this.tabPageInfo.Controls.Add(this.UI_labelDlInfo);
            this.tabPageInfo.Controls.Add(this.UI_labelWhInfo);
            this.tabPageInfo.Controls.Add(this.UI_labelRlInfo);
            this.tabPageInfo.Controls.Add(this.UI_labelAcInfo);
            this.tabPageInfo.Controls.Add(this.label6);
            this.tabPageInfo.Controls.Add(this.UI_Alarm);
            this.tabPageInfo.Controls.Add(this.UI_PoliceState);
            this.tabPageInfo.Controls.Add(this.UI_RoomlightState1);
            this.tabPageInfo.Controls.Add(this.UI_WaterheaterState1);
            this.tabPageInfo.Controls.Add(this.UI_DoorlightState1);
            this.tabPageInfo.Controls.Add(this.UI_AirconditionState1);
            this.tabPageInfo.Controls.Add(this.PC_buttonUpdate);
            this.tabPageInfo.Controls.Add(this.label5);
            this.tabPageInfo.Controls.Add(this.label4);
            this.tabPageInfo.Controls.Add(this.label3);
            this.tabPageInfo.Controls.Add(this.label2);
            this.tabPageInfo.Controls.Add(this.label1);
            this.tabPageInfo.Controls.Add(this.pictureBoxPolic);
            this.tabPageInfo.Controls.Add(this.UI_RoomLightBtn);
            this.tabPageInfo.Controls.Add(this.UI_WaterHeaterBtn);
            this.tabPageInfo.Controls.Add(this.UI_DoorLightBtn);
            this.tabPageInfo.Controls.Add(this.UI_AirConditionBtn);
            this.tabPageInfo.Controls.Add(this.groupBoxData);
            this.tabPageInfo.ImageIndex = 0;
            this.tabPageInfo.Location = new System.Drawing.Point(29, 4);
            this.tabPageInfo.Name = "tabPageInfo";
            this.tabPageInfo.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageInfo.Size = new System.Drawing.Size(611, 484);
            this.tabPageInfo.TabIndex = 0;
            this.tabPageInfo.Tag = "0";
            this.tabPageInfo.Text = "状态信息";
            this.tabPageInfo.UseVisualStyleBackColor = true;
            // 
            // PC_Unshow
            // 
            this.PC_Unshow.Location = new System.Drawing.Point(49, 18);
            this.PC_Unshow.Name = "PC_Unshow";
            this.PC_Unshow.Size = new System.Drawing.Size(100, 21);
            this.PC_Unshow.TabIndex = 33;
            this.PC_Unshow.Visible = false;
            // 
            // UI_labelWhTemp
            // 
            this.UI_labelWhTemp.AutoSize = true;
            this.UI_labelWhTemp.Font = new System.Drawing.Font("Comic Sans MS", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UI_labelWhTemp.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelWhTemp.Location = new System.Drawing.Point(265, 339);
            this.UI_labelWhTemp.Name = "UI_labelWhTemp";
            this.UI_labelWhTemp.Size = new System.Drawing.Size(0, 17);
            this.UI_labelWhTemp.TabIndex = 32;
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Font = new System.Drawing.Font("华文新魏", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label38.ForeColor = System.Drawing.Color.AliceBlue;
            this.label38.Location = new System.Drawing.Point(184, 339);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(77, 14);
            this.label38.TabIndex = 31;
            this.label38.Text = "温度设定：";
            // 
            // UI_labelAcTemp
            // 
            this.UI_labelAcTemp.AutoSize = true;
            this.UI_labelAcTemp.Font = new System.Drawing.Font("Comic Sans MS", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UI_labelAcTemp.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelAcTemp.Location = new System.Drawing.Point(265, 224);
            this.UI_labelAcTemp.Name = "UI_labelAcTemp";
            this.UI_labelAcTemp.Size = new System.Drawing.Size(0, 17);
            this.UI_labelAcTemp.TabIndex = 30;
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Font = new System.Drawing.Font("华文新魏", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label37.ForeColor = System.Drawing.Color.AliceBlue;
            this.label37.Location = new System.Drawing.Point(184, 225);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(77, 14);
            this.label37.TabIndex = 28;
            this.label37.Text = "温度设定：";
            // 
            // UI_labelDlInfo
            // 
            this.UI_labelDlInfo.AutoSize = true;
            this.UI_labelDlInfo.Font = new System.Drawing.Font("华文新魏", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_labelDlInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelDlInfo.Location = new System.Drawing.Point(363, 225);
            this.UI_labelDlInfo.Name = "UI_labelDlInfo";
            this.UI_labelDlInfo.Size = new System.Drawing.Size(77, 14);
            this.UI_labelDlInfo.TabIndex = 27;
            this.UI_labelDlInfo.Text = "　　无定时";
            // 
            // UI_labelWhInfo
            // 
            this.UI_labelWhInfo.AutoSize = true;
            this.UI_labelWhInfo.Font = new System.Drawing.Font("华文新魏", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_labelWhInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelWhInfo.Location = new System.Drawing.Point(44, 339);
            this.UI_labelWhInfo.Name = "UI_labelWhInfo";
            this.UI_labelWhInfo.Size = new System.Drawing.Size(77, 14);
            this.UI_labelWhInfo.TabIndex = 26;
            this.UI_labelWhInfo.Text = "　　无定时";
            // 
            // UI_labelRlInfo
            // 
            this.UI_labelRlInfo.AutoSize = true;
            this.UI_labelRlInfo.Font = new System.Drawing.Font("华文新魏", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_labelRlInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelRlInfo.Location = new System.Drawing.Point(363, 339);
            this.UI_labelRlInfo.Name = "UI_labelRlInfo";
            this.UI_labelRlInfo.Size = new System.Drawing.Size(77, 14);
            this.UI_labelRlInfo.TabIndex = 25;
            this.UI_labelRlInfo.Text = "　　无定时";
            // 
            // UI_labelAcInfo
            // 
            this.UI_labelAcInfo.AutoSize = true;
            this.UI_labelAcInfo.Font = new System.Drawing.Font("华文新魏", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_labelAcInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelAcInfo.Location = new System.Drawing.Point(44, 225);
            this.UI_labelAcInfo.Name = "UI_labelAcInfo";
            this.UI_labelAcInfo.Size = new System.Drawing.Size(77, 14);
            this.UI_labelAcInfo.TabIndex = 24;
            this.UI_labelAcInfo.Text = "　　无定时";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("华文新魏", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.ForeColor = System.Drawing.Color.AliceBlue;
            this.label6.Location = new System.Drawing.Point(314, 392);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(96, 19);
            this.label6.TabIndex = 23;
            this.label6.Text = "当前状态:";
            // 
            // UI_Alarm
            // 
            this.UI_Alarm.AutoSize = true;
            this.UI_Alarm.Font = new System.Drawing.Font("华文新魏", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_Alarm.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_Alarm.Location = new System.Drawing.Point(409, 392);
            this.UI_Alarm.Name = "UI_Alarm";
            this.UI_Alarm.Size = new System.Drawing.Size(85, 19);
            this.UI_Alarm.TabIndex = 22;
            this.UI_Alarm.Text = "一切正常";
            // 
            // UI_PoliceState
            // 
            this.UI_PoliceState.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_PoliceState.BackgroundImage")));
            this.UI_PoliceState.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_PoliceState.Location = new System.Drawing.Point(230, 380);
            this.UI_PoliceState.Name = "UI_PoliceState";
            this.UI_PoliceState.Size = new System.Drawing.Size(50, 50);
            this.UI_PoliceState.TabIndex = 21;
            this.UI_PoliceState.TabStop = false;
            // 
            // UI_RoomlightState1
            // 
            this.UI_RoomlightState1.BackgroundImage = global::南蛮入侵.Properties.Resources.绿灯;
            this.UI_RoomlightState1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_RoomlightState1.Location = new System.Drawing.Point(512, 274);
            this.UI_RoomlightState1.Name = "UI_RoomlightState1";
            this.UI_RoomlightState1.Size = new System.Drawing.Size(50, 50);
            this.UI_RoomlightState1.TabIndex = 20;
            this.UI_RoomlightState1.TabStop = false;
            this.UI_RoomlightState1.Click += new System.EventHandler(this.UI_RoomlightState1_Click);
            // 
            // UI_WaterheaterState1
            // 
            this.UI_WaterheaterState1.BackgroundImage = global::南蛮入侵.Properties.Resources.绿灯;
            this.UI_WaterheaterState1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_WaterheaterState1.Location = new System.Drawing.Point(231, 274);
            this.UI_WaterheaterState1.Name = "UI_WaterheaterState1";
            this.UI_WaterheaterState1.Size = new System.Drawing.Size(50, 50);
            this.UI_WaterheaterState1.TabIndex = 19;
            this.UI_WaterheaterState1.TabStop = false;
            this.UI_WaterheaterState1.Click += new System.EventHandler(this.UI_WaterheaterState1_Click);
            // 
            // UI_DoorlightState1
            // 
            this.UI_DoorlightState1.BackgroundImage = global::南蛮入侵.Properties.Resources.绿灯;
            this.UI_DoorlightState1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_DoorlightState1.Location = new System.Drawing.Point(512, 161);
            this.UI_DoorlightState1.Name = "UI_DoorlightState1";
            this.UI_DoorlightState1.Size = new System.Drawing.Size(50, 50);
            this.UI_DoorlightState1.TabIndex = 18;
            this.UI_DoorlightState1.TabStop = false;
            this.UI_DoorlightState1.Click += new System.EventHandler(this.UI_DoorlightState1_Click);
            // 
            // UI_AirconditionState1
            // 
            this.UI_AirconditionState1.BackgroundImage = global::南蛮入侵.Properties.Resources.绿灯;
            this.UI_AirconditionState1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_AirconditionState1.Location = new System.Drawing.Point(231, 161);
            this.UI_AirconditionState1.Name = "UI_AirconditionState1";
            this.UI_AirconditionState1.Size = new System.Drawing.Size(50, 50);
            this.UI_AirconditionState1.TabIndex = 13;
            this.UI_AirconditionState1.TabStop = false;
            this.UI_AirconditionState1.Click += new System.EventHandler(this.UI_AirconditionState1_Click);
            // 
            // PC_buttonUpdate
            // 
            this.PC_buttonUpdate.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_buttonUpdate.BackgroundImage")));
            this.PC_buttonUpdate.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_buttonUpdate.FlatAppearance.BorderSize = 0;
            this.PC_buttonUpdate.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_buttonUpdate.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_buttonUpdate.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_buttonUpdate.Location = new System.Drawing.Point(64, 65);
            this.PC_buttonUpdate.Name = "PC_buttonUpdate";
            this.PC_buttonUpdate.Size = new System.Drawing.Size(122, 42);
            this.PC_buttonUpdate.TabIndex = 12;
            this.PC_buttonUpdate.UseVisualStyleBackColor = true;
            this.PC_buttonUpdate.Click += new System.EventHandler(this.PC_buttonUpdate_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.ForeColor = System.Drawing.Color.AliceBlue;
            this.label5.Location = new System.Drawing.Point(154, 392);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(58, 22);
            this.label5.TabIndex = 11;
            this.label5.Text = "报警器";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.ForeColor = System.Drawing.Color.AliceBlue;
            this.label4.Location = new System.Drawing.Point(454, 290);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(58, 22);
            this.label4.TabIndex = 10;
            this.label4.Text = "卧室灯";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.ForeColor = System.Drawing.Color.AliceBlue;
            this.label3.Location = new System.Drawing.Point(454, 178);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(42, 22);
            this.label3.TabIndex = 9;
            this.label3.Text = "门灯";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.ForeColor = System.Drawing.Color.AliceBlue;
            this.label2.Location = new System.Drawing.Point(154, 290);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 22);
            this.label2.TabIndex = 8;
            this.label2.Text = "热水器";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.ForeColor = System.Drawing.Color.AliceBlue;
            this.label1.Location = new System.Drawing.Point(154, 178);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 22);
            this.label1.TabIndex = 7;
            this.label1.Text = "空调";
            // 
            // pictureBoxPolic
            // 
            this.pictureBoxPolic.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBoxPolic.BackgroundImage")));
            this.pictureBoxPolic.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBoxPolic.Location = new System.Drawing.Point(64, 382);
            this.pictureBoxPolic.Name = "pictureBoxPolic";
            this.pictureBoxPolic.Size = new System.Drawing.Size(59, 43);
            this.pictureBoxPolic.TabIndex = 6;
            this.pictureBoxPolic.TabStop = false;
            // 
            // UI_RoomLightBtn
            // 
            this.UI_RoomLightBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_RoomLightBtn.BackgroundImage")));
            this.UI_RoomLightBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_RoomLightBtn.FlatAppearance.BorderSize = 0;
            this.UI_RoomLightBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.UI_RoomLightBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.UI_RoomLightBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.UI_RoomLightBtn.Location = new System.Drawing.Point(370, 255);
            this.UI_RoomLightBtn.Name = "UI_RoomLightBtn";
            this.UI_RoomLightBtn.Size = new System.Drawing.Size(78, 69);
            this.UI_RoomLightBtn.TabIndex = 6;
            this.UI_RoomLightBtn.UseVisualStyleBackColor = true;
            this.UI_RoomLightBtn.Click += new System.EventHandler(this.UI_RoomLightBtn_Click);
            // 
            // UI_WaterHeaterBtn
            // 
            this.UI_WaterHeaterBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_WaterHeaterBtn.BackgroundImage")));
            this.UI_WaterHeaterBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_WaterHeaterBtn.FlatAppearance.BorderSize = 0;
            this.UI_WaterHeaterBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.UI_WaterHeaterBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.UI_WaterHeaterBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.UI_WaterHeaterBtn.Location = new System.Drawing.Point(49, 255);
            this.UI_WaterHeaterBtn.Name = "UI_WaterHeaterBtn";
            this.UI_WaterHeaterBtn.Size = new System.Drawing.Size(86, 69);
            this.UI_WaterHeaterBtn.TabIndex = 5;
            this.UI_WaterHeaterBtn.UseVisualStyleBackColor = true;
            this.UI_WaterHeaterBtn.Click += new System.EventHandler(this.UI_WaterHeaterBtn_Click);
            // 
            // UI_DoorLightBtn
            // 
            this.UI_DoorLightBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_DoorLightBtn.BackgroundImage")));
            this.UI_DoorLightBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_DoorLightBtn.FlatAppearance.BorderSize = 0;
            this.UI_DoorLightBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.UI_DoorLightBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.UI_DoorLightBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.UI_DoorLightBtn.Location = new System.Drawing.Point(362, 146);
            this.UI_DoorLightBtn.Name = "UI_DoorLightBtn";
            this.UI_DoorLightBtn.Size = new System.Drawing.Size(86, 69);
            this.UI_DoorLightBtn.TabIndex = 4;
            this.UI_DoorLightBtn.UseVisualStyleBackColor = true;
            this.UI_DoorLightBtn.Click += new System.EventHandler(this.UI_DoorLightBtn_Click);
            // 
            // UI_AirConditionBtn
            // 
            this.UI_AirConditionBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_AirConditionBtn.BackgroundImage")));
            this.UI_AirConditionBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_AirConditionBtn.FlatAppearance.BorderSize = 0;
            this.UI_AirConditionBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.UI_AirConditionBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.UI_AirConditionBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.UI_AirConditionBtn.Location = new System.Drawing.Point(49, 142);
            this.UI_AirConditionBtn.Name = "UI_AirConditionBtn";
            this.UI_AirConditionBtn.Size = new System.Drawing.Size(86, 69);
            this.UI_AirConditionBtn.TabIndex = 3;
            this.UI_AirConditionBtn.UseVisualStyleBackColor = true;
            this.UI_AirConditionBtn.Click += new System.EventHandler(this.UI_AirConditionBtn_Click);
            // 
            // groupBoxData
            // 
            this.groupBoxData.Controls.Add(this.UI_labelMode);
            this.groupBoxData.Controls.Add(this.pictureBox3);
            this.groupBoxData.Controls.Add(this.pictureBox2);
            this.groupBoxData.Controls.Add(this.pictureBox1);
            this.groupBoxData.Controls.Add(this.labelWeek);
            this.groupBoxData.Controls.Add(this.UI_labelConnect);
            this.groupBoxData.Controls.Add(this.UI_labelLight);
            this.groupBoxData.Controls.Add(this.UI_labelTemp);
            this.groupBoxData.Controls.Add(this.labelDate);
            this.groupBoxData.Controls.Add(this.labelTime);
            this.groupBoxData.Location = new System.Drawing.Point(302, 5);
            this.groupBoxData.Name = "groupBoxData";
            this.groupBoxData.Size = new System.Drawing.Size(296, 127);
            this.groupBoxData.TabIndex = 0;
            this.groupBoxData.TabStop = false;
            this.groupBoxData.Tag = "";
            // 
            // UI_labelMode
            // 
            this.UI_labelMode.AutoSize = true;
            this.UI_labelMode.Font = new System.Drawing.Font("华文新魏", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_labelMode.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelMode.Location = new System.Drawing.Point(21, 104);
            this.UI_labelMode.Name = "UI_labelMode";
            this.UI_labelMode.Size = new System.Drawing.Size(76, 17);
            this.UI_labelMode.TabIndex = 10;
            this.UI_labelMode.Text = "普通模式";
            // 
            // pictureBox3
            // 
            this.pictureBox3.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox3.BackgroundImage")));
            this.pictureBox3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox3.Location = new System.Drawing.Point(92, 36);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(26, 27);
            this.pictureBox3.TabIndex = 8;
            this.pictureBox3.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox2.BackgroundImage")));
            this.pictureBox2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox2.Location = new System.Drawing.Point(7, 48);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(25, 23);
            this.pictureBox2.TabIndex = 7;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox1.Location = new System.Drawing.Point(3, 20);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(31, 23);
            this.pictureBox1.TabIndex = 6;
            this.pictureBox1.TabStop = false;
            // 
            // labelWeek
            // 
            this.labelWeek.AutoSize = true;
            this.labelWeek.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelWeek.ForeColor = System.Drawing.Color.AliceBlue;
            this.labelWeek.Location = new System.Drawing.Point(226, 88);
            this.labelWeek.Name = "labelWeek";
            this.labelWeek.Size = new System.Drawing.Size(52, 19);
            this.labelWeek.TabIndex = 5;
            this.labelWeek.Text = "Friday";
            // 
            // UI_labelConnect
            // 
            this.UI_labelConnect.AutoSize = true;
            this.UI_labelConnect.Font = new System.Drawing.Font("华文新魏", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_labelConnect.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelConnect.Location = new System.Drawing.Point(10, 77);
            this.UI_labelConnect.Name = "UI_labelConnect";
            this.UI_labelConnect.Size = new System.Drawing.Size(110, 17);
            this.UI_labelConnect.TabIndex = 4;
            this.UI_labelConnect.Text = "未连接下位机";
            // 
            // UI_labelLight
            // 
            this.UI_labelLight.AutoSize = true;
            this.UI_labelLight.Font = new System.Drawing.Font("Comic Sans MS", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UI_labelLight.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelLight.Location = new System.Drawing.Point(35, 44);
            this.UI_labelLight.Name = "UI_labelLight";
            this.UI_labelLight.Size = new System.Drawing.Size(46, 27);
            this.UI_labelLight.TabIndex = 3;
            this.UI_labelLight.Text = "50L";
            // 
            // UI_labelTemp
            // 
            this.UI_labelTemp.AutoSize = true;
            this.UI_labelTemp.Font = new System.Drawing.Font("Comic Sans MS", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UI_labelTemp.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_labelTemp.Location = new System.Drawing.Point(35, 17);
            this.UI_labelTemp.Name = "UI_labelTemp";
            this.UI_labelTemp.Size = new System.Drawing.Size(57, 27);
            this.UI_labelTemp.TabIndex = 2;
            this.UI_labelTemp.Text = "25℃";
            // 
            // labelDate
            // 
            this.labelDate.AutoSize = true;
            this.labelDate.Font = new System.Drawing.Font("Comic Sans MS", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelDate.ForeColor = System.Drawing.Color.AliceBlue;
            this.labelDate.Location = new System.Drawing.Point(133, 88);
            this.labelDate.Name = "labelDate";
            this.labelDate.Size = new System.Drawing.Size(86, 19);
            this.labelDate.TabIndex = 1;
            this.labelDate.Text = "2013/7/26";
            // 
            // labelTime
            // 
            this.labelTime.AutoSize = true;
            this.labelTime.Font = new System.Drawing.Font("Comic Sans MS", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTime.ForeColor = System.Drawing.Color.AliceBlue;
            this.labelTime.Location = new System.Drawing.Point(123, 13);
            this.labelTime.Name = "labelTime";
            this.labelTime.Size = new System.Drawing.Size(166, 67);
            this.labelTime.TabIndex = 0;
            this.labelTime.Text = "12:40";
            // 
            // tabPageControl
            // 
            this.tabPageControl.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("tabPageControl.BackgroundImage")));
            this.tabPageControl.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPageControl.Controls.Add(this.tabControl2);
            this.tabPageControl.ImageIndex = 1;
            this.tabPageControl.Location = new System.Drawing.Point(29, 4);
            this.tabPageControl.Name = "tabPageControl";
            this.tabPageControl.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageControl.Size = new System.Drawing.Size(611, 484);
            this.tabPageControl.TabIndex = 1;
            this.tabPageControl.Tag = "";
            this.tabPageControl.Text = "电器控制";
            this.tabPageControl.UseVisualStyleBackColor = true;
            // 
            // tabControl2
            // 
            this.tabControl2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl2.Controls.Add(this.tabPageAir);
            this.tabControl2.Controls.Add(this.tabPageHot);
            this.tabControl2.Controls.Add(this.tabPageDoor);
            this.tabControl2.Controls.Add(this.tabPageBed);
            this.tabControl2.ItemSize = new System.Drawing.Size(48, 20);
            this.tabControl2.Location = new System.Drawing.Point(0, 0);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(615, 478);
            this.tabControl2.TabIndex = 0;
            this.tabControl2.Tag = "";
            // 
            // tabPageAir
            // 
            this.tabPageAir.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("tabPageAir.BackgroundImage")));
            this.tabPageAir.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPageAir.Controls.Add(this.pictureBox4);
            this.tabPageAir.Controls.Add(this.groupBox1);
            this.tabPageAir.Location = new System.Drawing.Point(4, 24);
            this.tabPageAir.Name = "tabPageAir";
            this.tabPageAir.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageAir.Size = new System.Drawing.Size(607, 450);
            this.tabPageAir.TabIndex = 0;
            this.tabPageAir.Tag = "0";
            this.tabPageAir.Text = "空调";
            this.tabPageAir.UseVisualStyleBackColor = true;
            // 
            // pictureBox4
            // 
            this.pictureBox4.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox4.BackgroundImage")));
            this.pictureBox4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox4.Location = new System.Drawing.Point(64, 6);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(95, 75);
            this.pictureBox4.TabIndex = 5;
            this.pictureBox4.TabStop = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.UI_AcSetTimeComboBox);
            this.groupBox1.Controls.Add(this.UI_AcSetTempInfo);
            this.groupBox1.Controls.Add(this.label39);
            this.groupBox1.Controls.Add(this.UI_AcSetTimeInfo);
            this.groupBox1.Controls.Add(this.label0);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.UI_AcTimeSetHour);
            this.groupBox1.Controls.Add(this.UI_AcTimeSetMinute);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.UI_AcTempSet);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.UI_AirconditionState2);
            this.groupBox1.Controls.Add(this.PC_AirConditionBtn);
            this.groupBox1.Controls.Add(this.PC_AcTempSetBtn);
            this.groupBox1.Controls.Add(this.PC_AcTimeCancelBtn);
            this.groupBox1.Controls.Add(this.PC_AcTimeSetBtn);
            this.groupBox1.Location = new System.Drawing.Point(55, 42);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(500, 357);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            // 
            // UI_AcSetTimeComboBox
            // 
            this.UI_AcSetTimeComboBox.BackColor = System.Drawing.SystemColors.Window;
            this.UI_AcSetTimeComboBox.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_AcSetTimeComboBox.ForeColor = System.Drawing.Color.DodgerBlue;
            this.UI_AcSetTimeComboBox.FormattingEnabled = true;
            this.UI_AcSetTimeComboBox.Items.AddRange(new object[] {
            "开",
            "关"});
            this.UI_AcSetTimeComboBox.Location = new System.Drawing.Point(279, 265);
            this.UI_AcSetTimeComboBox.Name = "UI_AcSetTimeComboBox";
            this.UI_AcSetTimeComboBox.Size = new System.Drawing.Size(42, 27);
            this.UI_AcSetTimeComboBox.TabIndex = 16;
            // 
            // UI_AcSetTempInfo
            // 
            this.UI_AcSetTempInfo.AutoSize = true;
            this.UI_AcSetTempInfo.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UI_AcSetTempInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_AcSetTempInfo.Location = new System.Drawing.Point(188, 188);
            this.UI_AcSetTempInfo.Name = "UI_AcSetTempInfo";
            this.UI_AcSetTempInfo.Size = new System.Drawing.Size(0, 23);
            this.UI_AcSetTempInfo.TabIndex = 15;
            // 
            // label39
            // 
            this.label39.AutoSize = true;
            this.label39.Font = new System.Drawing.Font("华文新魏", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label39.ForeColor = System.Drawing.Color.AliceBlue;
            this.label39.Location = new System.Drawing.Point(43, 188);
            this.label39.Name = "label39";
            this.label39.Size = new System.Drawing.Size(142, 19);
            this.label39.TabIndex = 14;
            this.label39.Text = "当前设定温度：";
            // 
            // UI_AcSetTimeInfo
            // 
            this.UI_AcSetTimeInfo.AutoSize = true;
            this.UI_AcSetTimeInfo.Font = new System.Drawing.Font("华文新魏", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_AcSetTimeInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_AcSetTimeInfo.Location = new System.Drawing.Point(43, 311);
            this.UI_AcSetTimeInfo.Name = "UI_AcSetTimeInfo";
            this.UI_AcSetTimeInfo.Size = new System.Drawing.Size(104, 19);
            this.UI_AcSetTimeInfo.TabIndex = 13;
            this.UI_AcSetTimeInfo.Text = "　　无定时";
            // 
            // label0
            // 
            this.label0.AutoSize = true;
            this.label0.Font = new System.Drawing.Font("Comic Sans MS", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label0.ForeColor = System.Drawing.Color.AliceBlue;
            this.label0.Location = new System.Drawing.Point(257, 144);
            this.label0.Name = "label0";
            this.label0.Size = new System.Drawing.Size(33, 27);
            this.label0.TabIndex = 11;
            this.label0.Text = "℃";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.ForeColor = System.Drawing.Color.AliceBlue;
            this.label7.Location = new System.Drawing.Point(128, 265);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(31, 26);
            this.label7.TabIndex = 10;
            this.label7.Text = "时";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.ForeColor = System.Drawing.Color.AliceBlue;
            this.label8.Location = new System.Drawing.Point(242, 265);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(31, 26);
            this.label8.TabIndex = 9;
            this.label8.Text = "分";
            // 
            // UI_AcTimeSetHour
            // 
            this.UI_AcTimeSetHour.Location = new System.Drawing.Point(47, 270);
            this.UI_AcTimeSetHour.MaxLength = 2;
            this.UI_AcTimeSetHour.Name = "UI_AcTimeSetHour";
            this.UI_AcTimeSetHour.Size = new System.Drawing.Size(73, 21);
            this.UI_AcTimeSetHour.TabIndex = 6;
            this.UI_AcTimeSetHour.Text = "0";
            this.UI_AcTimeSetHour.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_AcTimeSetHour_KeyPress);
            // 
            // UI_AcTimeSetMinute
            // 
            this.UI_AcTimeSetMinute.Location = new System.Drawing.Point(163, 270);
            this.UI_AcTimeSetMinute.MaxLength = 2;
            this.UI_AcTimeSetMinute.Name = "UI_AcTimeSetMinute";
            this.UI_AcTimeSetMinute.Size = new System.Drawing.Size(73, 21);
            this.UI_AcTimeSetMinute.TabIndex = 7;
            this.UI_AcTimeSetMinute.Text = "0";
            this.UI_AcTimeSetMinute.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_AcTimeSetMinute_KeyPress);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label9.ForeColor = System.Drawing.Color.AliceBlue;
            this.label9.Location = new System.Drawing.Point(42, 75);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(117, 28);
            this.label9.TabIndex = 8;
            this.label9.Text = "开关设定：";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label10.ForeColor = System.Drawing.Color.AliceBlue;
            this.label10.Location = new System.Drawing.Point(42, 227);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(102, 28);
            this.label10.TabIndex = 7;
            this.label10.Text = "定时设定:";
            // 
            // UI_AcTempSet
            // 
            this.UI_AcTempSet.Location = new System.Drawing.Point(181, 150);
            this.UI_AcTempSet.Name = "UI_AcTempSet";
            this.UI_AcTempSet.Size = new System.Drawing.Size(70, 21);
            this.UI_AcTempSet.TabIndex = 6;
            this.UI_AcTempSet.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox3_KeyPress);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label11.ForeColor = System.Drawing.Color.AliceBlue;
            this.label11.Location = new System.Drawing.Point(42, 143);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(102, 28);
            this.label11.TabIndex = 5;
            this.label11.Text = "温度设定:";
            // 
            // UI_AirconditionState2
            // 
            this.UI_AirconditionState2.BackgroundImage = global::南蛮入侵.Properties.Resources.绿灯;
            this.UI_AirconditionState2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_AirconditionState2.Location = new System.Drawing.Point(197, 75);
            this.UI_AirconditionState2.Name = "UI_AirconditionState2";
            this.UI_AirconditionState2.Size = new System.Drawing.Size(41, 39);
            this.UI_AirconditionState2.TabIndex = 4;
            this.UI_AirconditionState2.TabStop = false;
            // 
            // PC_AirConditionBtn
            // 
            this.PC_AirConditionBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_AirConditionBtn.BackgroundImage")));
            this.PC_AirConditionBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_AirConditionBtn.FlatAppearance.BorderSize = 0;
            this.PC_AirConditionBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_AirConditionBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_AirConditionBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_AirConditionBtn.Location = new System.Drawing.Point(297, 63);
            this.PC_AirConditionBtn.Name = "PC_AirConditionBtn";
            this.PC_AirConditionBtn.Size = new System.Drawing.Size(55, 52);
            this.PC_AirConditionBtn.TabIndex = 3;
            this.PC_AirConditionBtn.UseVisualStyleBackColor = true;
            this.PC_AirConditionBtn.Click += new System.EventHandler(this.PC_AirConditionBtn_Click);
            // 
            // PC_AcTempSetBtn
            // 
            this.PC_AcTempSetBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_AcTempSetBtn.BackgroundImage")));
            this.PC_AcTempSetBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_AcTempSetBtn.FlatAppearance.BorderSize = 0;
            this.PC_AcTempSetBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_AcTempSetBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_AcTempSetBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_AcTempSetBtn.Location = new System.Drawing.Point(359, 132);
            this.PC_AcTempSetBtn.Name = "PC_AcTempSetBtn";
            this.PC_AcTempSetBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_AcTempSetBtn.TabIndex = 2;
            this.PC_AcTempSetBtn.Tag = "";
            this.PC_AcTempSetBtn.UseVisualStyleBackColor = true;
            this.PC_AcTempSetBtn.Click += new System.EventHandler(this.PC_AcTempSetBtn_Click);
            // 
            // PC_AcTimeCancelBtn
            // 
            this.PC_AcTimeCancelBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_AcTimeCancelBtn.BackgroundImage")));
            this.PC_AcTimeCancelBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_AcTimeCancelBtn.FlatAppearance.BorderSize = 0;
            this.PC_AcTimeCancelBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_AcTimeCancelBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_AcTimeCancelBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_AcTimeCancelBtn.Location = new System.Drawing.Point(359, 294);
            this.PC_AcTimeCancelBtn.Name = "PC_AcTimeCancelBtn";
            this.PC_AcTimeCancelBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_AcTimeCancelBtn.TabIndex = 1;
            this.PC_AcTimeCancelBtn.Tag = "";
            this.PC_AcTimeCancelBtn.UseVisualStyleBackColor = true;
            this.PC_AcTimeCancelBtn.Click += new System.EventHandler(this.PC_AcTimeCancelBtn_Click);
            // 
            // PC_AcTimeSetBtn
            // 
            this.PC_AcTimeSetBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_AcTimeSetBtn.BackgroundImage")));
            this.PC_AcTimeSetBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_AcTimeSetBtn.FlatAppearance.BorderSize = 0;
            this.PC_AcTimeSetBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_AcTimeSetBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_AcTimeSetBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_AcTimeSetBtn.Location = new System.Drawing.Point(359, 227);
            this.PC_AcTimeSetBtn.Name = "PC_AcTimeSetBtn";
            this.PC_AcTimeSetBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_AcTimeSetBtn.TabIndex = 0;
            this.PC_AcTimeSetBtn.Tag = "";
            this.PC_AcTimeSetBtn.UseVisualStyleBackColor = true;
            this.PC_AcTimeSetBtn.Click += new System.EventHandler(this.PC_AcTimeSetBtn_Click);
            // 
            // tabPageHot
            // 
            this.tabPageHot.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("tabPageHot.BackgroundImage")));
            this.tabPageHot.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPageHot.Controls.Add(this.pictureBox5);
            this.tabPageHot.Controls.Add(this.groupBox2);
            this.tabPageHot.Location = new System.Drawing.Point(4, 24);
            this.tabPageHot.Name = "tabPageHot";
            this.tabPageHot.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageHot.Size = new System.Drawing.Size(607, 450);
            this.tabPageHot.TabIndex = 1;
            this.tabPageHot.Tag = "0";
            this.tabPageHot.Text = "热水器";
            this.tabPageHot.UseVisualStyleBackColor = true;
            // 
            // pictureBox5
            // 
            this.pictureBox5.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox5.BackgroundImage")));
            this.pictureBox5.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox5.Location = new System.Drawing.Point(64, 6);
            this.pictureBox5.Name = "pictureBox5";
            this.pictureBox5.Size = new System.Drawing.Size(96, 77);
            this.pictureBox5.TabIndex = 6;
            this.pictureBox5.TabStop = false;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.UI_WhSetTimeListBox);
            this.groupBox2.Controls.Add(this.UI_WhSetTempInfo);
            this.groupBox2.Controls.Add(this.label41);
            this.groupBox2.Controls.Add(this.UI_WhSetTimeInfo);
            this.groupBox2.Controls.Add(this.label14);
            this.groupBox2.Controls.Add(this.label12);
            this.groupBox2.Controls.Add(this.label13);
            this.groupBox2.Controls.Add(this.UI_WhTimeSetHour);
            this.groupBox2.Controls.Add(this.UI_WhTimeSetMinute);
            this.groupBox2.Controls.Add(this.label15);
            this.groupBox2.Controls.Add(this.label17);
            this.groupBox2.Controls.Add(this.UI_WhTempSet);
            this.groupBox2.Controls.Add(this.label16);
            this.groupBox2.Controls.Add(this.UI_WaterheaterState2);
            this.groupBox2.Controls.Add(this.PC_WaterHeaterBtn);
            this.groupBox2.Controls.Add(this.PC_WhTempSetBtn);
            this.groupBox2.Controls.Add(this.PC_WhTimeCancelBtn);
            this.groupBox2.Controls.Add(this.PC_WhTimeSetBtn);
            this.groupBox2.Location = new System.Drawing.Point(56, 42);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(500, 357);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            // 
            // UI_WhSetTimeListBox
            // 
            this.UI_WhSetTimeListBox.BackColor = System.Drawing.SystemColors.Window;
            this.UI_WhSetTimeListBox.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_WhSetTimeListBox.ForeColor = System.Drawing.Color.DodgerBlue;
            this.UI_WhSetTimeListBox.FormattingEnabled = true;
            this.UI_WhSetTimeListBox.Items.AddRange(new object[] {
            "开",
            "关"});
            this.UI_WhSetTimeListBox.Location = new System.Drawing.Point(279, 264);
            this.UI_WhSetTimeListBox.Name = "UI_WhSetTimeListBox";
            this.UI_WhSetTimeListBox.Size = new System.Drawing.Size(42, 27);
            this.UI_WhSetTimeListBox.TabIndex = 17;
            // 
            // UI_WhSetTempInfo
            // 
            this.UI_WhSetTempInfo.AutoSize = true;
            this.UI_WhSetTempInfo.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UI_WhSetTempInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_WhSetTempInfo.Location = new System.Drawing.Point(190, 190);
            this.UI_WhSetTempInfo.Name = "UI_WhSetTempInfo";
            this.UI_WhSetTempInfo.Size = new System.Drawing.Size(0, 23);
            this.UI_WhSetTempInfo.TabIndex = 16;
            // 
            // label41
            // 
            this.label41.AutoSize = true;
            this.label41.Font = new System.Drawing.Font("华文新魏", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label41.ForeColor = System.Drawing.Color.AliceBlue;
            this.label41.Location = new System.Drawing.Point(43, 190);
            this.label41.Name = "label41";
            this.label41.Size = new System.Drawing.Size(142, 19);
            this.label41.TabIndex = 15;
            this.label41.Text = "当前设定温度：";
            // 
            // UI_WhSetTimeInfo
            // 
            this.UI_WhSetTimeInfo.AutoSize = true;
            this.UI_WhSetTimeInfo.Font = new System.Drawing.Font("华文新魏", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_WhSetTimeInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_WhSetTimeInfo.Location = new System.Drawing.Point(43, 311);
            this.UI_WhSetTimeInfo.Name = "UI_WhSetTimeInfo";
            this.UI_WhSetTimeInfo.Size = new System.Drawing.Size(104, 19);
            this.UI_WhSetTimeInfo.TabIndex = 14;
            this.UI_WhSetTimeInfo.Text = "　　无定时";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Comic Sans MS", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.ForeColor = System.Drawing.Color.AliceBlue;
            this.label14.Location = new System.Drawing.Point(258, 145);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(33, 27);
            this.label14.TabIndex = 11;
            this.label14.Text = "℃";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label12.ForeColor = System.Drawing.Color.AliceBlue;
            this.label12.Location = new System.Drawing.Point(128, 264);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(31, 26);
            this.label12.TabIndex = 10;
            this.label12.Text = "时";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label13.ForeColor = System.Drawing.Color.AliceBlue;
            this.label13.Location = new System.Drawing.Point(242, 263);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(31, 26);
            this.label13.TabIndex = 9;
            this.label13.Text = "分";
            // 
            // UI_WhTimeSetHour
            // 
            this.UI_WhTimeSetHour.Location = new System.Drawing.Point(47, 268);
            this.UI_WhTimeSetHour.MaxLength = 2;
            this.UI_WhTimeSetHour.Name = "UI_WhTimeSetHour";
            this.UI_WhTimeSetHour.Size = new System.Drawing.Size(73, 21);
            this.UI_WhTimeSetHour.TabIndex = 6;
            this.UI_WhTimeSetHour.Text = "0";
            this.UI_WhTimeSetHour.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_WhTimeSetHour_KeyPress);
            // 
            // UI_WhTimeSetMinute
            // 
            this.UI_WhTimeSetMinute.Location = new System.Drawing.Point(163, 268);
            this.UI_WhTimeSetMinute.MaxLength = 2;
            this.UI_WhTimeSetMinute.Name = "UI_WhTimeSetMinute";
            this.UI_WhTimeSetMinute.Size = new System.Drawing.Size(73, 21);
            this.UI_WhTimeSetMinute.TabIndex = 7;
            this.UI_WhTimeSetMinute.Text = "0";
            this.UI_WhTimeSetMinute.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_WhTimeSetMinute_KeyPress);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label15.ForeColor = System.Drawing.Color.AliceBlue;
            this.label15.Location = new System.Drawing.Point(42, 75);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(117, 28);
            this.label15.TabIndex = 8;
            this.label15.Text = "开关设定：";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label17.ForeColor = System.Drawing.Color.AliceBlue;
            this.label17.Location = new System.Drawing.Point(42, 226);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(102, 28);
            this.label17.TabIndex = 7;
            this.label17.Text = "定时设定:";
            // 
            // UI_WhTempSet
            // 
            this.UI_WhTempSet.Location = new System.Drawing.Point(182, 151);
            this.UI_WhTempSet.Name = "UI_WhTempSet";
            this.UI_WhTempSet.Size = new System.Drawing.Size(70, 21);
            this.UI_WhTempSet.TabIndex = 6;
            this.UI_WhTempSet.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox6_KeyPress);
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label16.ForeColor = System.Drawing.Color.AliceBlue;
            this.label16.Location = new System.Drawing.Point(42, 143);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(102, 28);
            this.label16.TabIndex = 5;
            this.label16.Text = "温度设定:";
            // 
            // UI_WaterheaterState2
            // 
            this.UI_WaterheaterState2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_WaterheaterState2.BackgroundImage")));
            this.UI_WaterheaterState2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_WaterheaterState2.Location = new System.Drawing.Point(197, 75);
            this.UI_WaterheaterState2.Name = "UI_WaterheaterState2";
            this.UI_WaterheaterState2.Size = new System.Drawing.Size(41, 39);
            this.UI_WaterheaterState2.TabIndex = 4;
            this.UI_WaterheaterState2.TabStop = false;
            // 
            // PC_WaterHeaterBtn
            // 
            this.PC_WaterHeaterBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_WaterHeaterBtn.BackgroundImage")));
            this.PC_WaterHeaterBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_WaterHeaterBtn.FlatAppearance.BorderSize = 0;
            this.PC_WaterHeaterBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_WaterHeaterBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_WaterHeaterBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_WaterHeaterBtn.Location = new System.Drawing.Point(297, 63);
            this.PC_WaterHeaterBtn.Name = "PC_WaterHeaterBtn";
            this.PC_WaterHeaterBtn.Size = new System.Drawing.Size(55, 52);
            this.PC_WaterHeaterBtn.TabIndex = 3;
            this.PC_WaterHeaterBtn.UseVisualStyleBackColor = true;
            this.PC_WaterHeaterBtn.Click += new System.EventHandler(this.PC_WaterHeaterBtn_Click);
            // 
            // PC_WhTempSetBtn
            // 
            this.PC_WhTempSetBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_WhTempSetBtn.BackgroundImage")));
            this.PC_WhTempSetBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_WhTempSetBtn.FlatAppearance.BorderSize = 0;
            this.PC_WhTempSetBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_WhTempSetBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_WhTempSetBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_WhTempSetBtn.Location = new System.Drawing.Point(359, 141);
            this.PC_WhTempSetBtn.Name = "PC_WhTempSetBtn";
            this.PC_WhTempSetBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_WhTempSetBtn.TabIndex = 2;
            this.PC_WhTempSetBtn.Tag = "";
            this.PC_WhTempSetBtn.UseVisualStyleBackColor = true;
            this.PC_WhTempSetBtn.Click += new System.EventHandler(this.PC_WhTempSetBtn_Click);
            // 
            // PC_WhTimeCancelBtn
            // 
            this.PC_WhTimeCancelBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_WhTimeCancelBtn.BackgroundImage")));
            this.PC_WhTimeCancelBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_WhTimeCancelBtn.FlatAppearance.BorderSize = 0;
            this.PC_WhTimeCancelBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_WhTimeCancelBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_WhTimeCancelBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_WhTimeCancelBtn.Location = new System.Drawing.Point(359, 294);
            this.PC_WhTimeCancelBtn.Name = "PC_WhTimeCancelBtn";
            this.PC_WhTimeCancelBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_WhTimeCancelBtn.TabIndex = 1;
            this.PC_WhTimeCancelBtn.Tag = "";
            this.PC_WhTimeCancelBtn.UseVisualStyleBackColor = true;
            this.PC_WhTimeCancelBtn.Click += new System.EventHandler(this.PC_WhTimeCancelBtn_Click);
            // 
            // PC_WhTimeSetBtn
            // 
            this.PC_WhTimeSetBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_WhTimeSetBtn.BackgroundImage")));
            this.PC_WhTimeSetBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_WhTimeSetBtn.FlatAppearance.BorderSize = 0;
            this.PC_WhTimeSetBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_WhTimeSetBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_WhTimeSetBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_WhTimeSetBtn.Location = new System.Drawing.Point(359, 229);
            this.PC_WhTimeSetBtn.Name = "PC_WhTimeSetBtn";
            this.PC_WhTimeSetBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_WhTimeSetBtn.TabIndex = 0;
            this.PC_WhTimeSetBtn.Tag = "";
            this.PC_WhTimeSetBtn.UseVisualStyleBackColor = true;
            this.PC_WhTimeSetBtn.Click += new System.EventHandler(this.PC_WhTimeSetBtn_Click);
            // 
            // tabPageDoor
            // 
            this.tabPageDoor.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("tabPageDoor.BackgroundImage")));
            this.tabPageDoor.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPageDoor.Controls.Add(this.pictureBox6);
            this.tabPageDoor.Controls.Add(this.groupBox3);
            this.tabPageDoor.Location = new System.Drawing.Point(4, 24);
            this.tabPageDoor.Name = "tabPageDoor";
            this.tabPageDoor.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageDoor.Size = new System.Drawing.Size(607, 450);
            this.tabPageDoor.TabIndex = 2;
            this.tabPageDoor.Tag = "0";
            this.tabPageDoor.Text = "门灯";
            this.tabPageDoor.UseVisualStyleBackColor = true;
            // 
            // pictureBox6
            // 
            this.pictureBox6.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox6.BackgroundImage")));
            this.pictureBox6.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox6.Location = new System.Drawing.Point(61, 10);
            this.pictureBox6.Name = "pictureBox6";
            this.pictureBox6.Size = new System.Drawing.Size(95, 69);
            this.pictureBox6.TabIndex = 6;
            this.pictureBox6.TabStop = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.UI_DlSetTimeListBox);
            this.groupBox3.Controls.Add(this.UI_DlSetTimeInfo);
            this.groupBox3.Controls.Add(this.PC_DoorLightBtn);
            this.groupBox3.Controls.Add(this.UI_DoorlightState2);
            this.groupBox3.Controls.Add(this.label20);
            this.groupBox3.Controls.Add(this.label21);
            this.groupBox3.Controls.Add(this.UI_DlTimeSetHour);
            this.groupBox3.Controls.Add(this.UI_DlTimeSetMinute);
            this.groupBox3.Controls.Add(this.label18);
            this.groupBox3.Controls.Add(this.label19);
            this.groupBox3.Controls.Add(this.PC_DlTimeCancelBtn);
            this.groupBox3.Controls.Add(this.PC_DlTimeSetBtn);
            this.groupBox3.Location = new System.Drawing.Point(53, 40);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(500, 350);
            this.groupBox3.TabIndex = 7;
            this.groupBox3.TabStop = false;
            // 
            // UI_DlSetTimeListBox
            // 
            this.UI_DlSetTimeListBox.BackColor = System.Drawing.SystemColors.Window;
            this.UI_DlSetTimeListBox.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_DlSetTimeListBox.ForeColor = System.Drawing.Color.DodgerBlue;
            this.UI_DlSetTimeListBox.FormattingEnabled = true;
            this.UI_DlSetTimeListBox.Items.AddRange(new object[] {
            "开",
            "关"});
            this.UI_DlSetTimeListBox.Location = new System.Drawing.Point(282, 210);
            this.UI_DlSetTimeListBox.Name = "UI_DlSetTimeListBox";
            this.UI_DlSetTimeListBox.Size = new System.Drawing.Size(42, 27);
            this.UI_DlSetTimeListBox.TabIndex = 18;
            // 
            // UI_DlSetTimeInfo
            // 
            this.UI_DlSetTimeInfo.AutoSize = true;
            this.UI_DlSetTimeInfo.Font = new System.Drawing.Font("华文新魏", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_DlSetTimeInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_DlSetTimeInfo.Location = new System.Drawing.Point(43, 273);
            this.UI_DlSetTimeInfo.Name = "UI_DlSetTimeInfo";
            this.UI_DlSetTimeInfo.Size = new System.Drawing.Size(104, 19);
            this.UI_DlSetTimeInfo.TabIndex = 12;
            this.UI_DlSetTimeInfo.Text = "　　无定时";
            // 
            // PC_DoorLightBtn
            // 
            this.PC_DoorLightBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_DoorLightBtn.BackgroundImage")));
            this.PC_DoorLightBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_DoorLightBtn.FlatAppearance.BorderSize = 0;
            this.PC_DoorLightBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_DoorLightBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_DoorLightBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_DoorLightBtn.Location = new System.Drawing.Point(297, 67);
            this.PC_DoorLightBtn.Name = "PC_DoorLightBtn";
            this.PC_DoorLightBtn.Size = new System.Drawing.Size(55, 52);
            this.PC_DoorLightBtn.TabIndex = 3;
            this.PC_DoorLightBtn.UseVisualStyleBackColor = true;
            this.PC_DoorLightBtn.Click += new System.EventHandler(this.PC_DoorLightBtn_Click);
            // 
            // UI_DoorlightState2
            // 
            this.UI_DoorlightState2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_DoorlightState2.BackgroundImage")));
            this.UI_DoorlightState2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_DoorlightState2.Location = new System.Drawing.Point(198, 75);
            this.UI_DoorlightState2.Name = "UI_DoorlightState2";
            this.UI_DoorlightState2.Size = new System.Drawing.Size(41, 39);
            this.UI_DoorlightState2.TabIndex = 4;
            this.UI_DoorlightState2.TabStop = false;
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label20.ForeColor = System.Drawing.Color.AliceBlue;
            this.label20.Location = new System.Drawing.Point(128, 213);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(31, 26);
            this.label20.TabIndex = 10;
            this.label20.Text = "时";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label21.ForeColor = System.Drawing.Color.AliceBlue;
            this.label21.Location = new System.Drawing.Point(245, 212);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(31, 26);
            this.label21.TabIndex = 9;
            this.label21.Text = "分";
            // 
            // UI_DlTimeSetHour
            // 
            this.UI_DlTimeSetHour.Location = new System.Drawing.Point(47, 217);
            this.UI_DlTimeSetHour.MaxLength = 2;
            this.UI_DlTimeSetHour.Name = "UI_DlTimeSetHour";
            this.UI_DlTimeSetHour.Size = new System.Drawing.Size(73, 21);
            this.UI_DlTimeSetHour.TabIndex = 6;
            this.UI_DlTimeSetHour.Text = "0";
            // 
            // UI_DlTimeSetMinute
            // 
            this.UI_DlTimeSetMinute.Location = new System.Drawing.Point(166, 217);
            this.UI_DlTimeSetMinute.MaxLength = 2;
            this.UI_DlTimeSetMinute.Name = "UI_DlTimeSetMinute";
            this.UI_DlTimeSetMinute.Size = new System.Drawing.Size(73, 21);
            this.UI_DlTimeSetMinute.TabIndex = 7;
            this.UI_DlTimeSetMinute.Text = "0";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label18.ForeColor = System.Drawing.Color.AliceBlue;
            this.label18.Location = new System.Drawing.Point(42, 75);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(117, 28);
            this.label18.TabIndex = 8;
            this.label18.Text = "开关设定：";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label19.ForeColor = System.Drawing.Color.AliceBlue;
            this.label19.Location = new System.Drawing.Point(42, 156);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(102, 28);
            this.label19.TabIndex = 7;
            this.label19.Text = "定时设定:";
            // 
            // PC_DlTimeCancelBtn
            // 
            this.PC_DlTimeCancelBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_DlTimeCancelBtn.BackgroundImage")));
            this.PC_DlTimeCancelBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_DlTimeCancelBtn.FlatAppearance.BorderSize = 0;
            this.PC_DlTimeCancelBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_DlTimeCancelBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_DlTimeCancelBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_DlTimeCancelBtn.Location = new System.Drawing.Point(362, 273);
            this.PC_DlTimeCancelBtn.Name = "PC_DlTimeCancelBtn";
            this.PC_DlTimeCancelBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_DlTimeCancelBtn.TabIndex = 1;
            this.PC_DlTimeCancelBtn.Tag = "";
            this.PC_DlTimeCancelBtn.UseVisualStyleBackColor = true;
            this.PC_DlTimeCancelBtn.Click += new System.EventHandler(this.PC_DlTimeCancelBtn_Click);
            // 
            // PC_DlTimeSetBtn
            // 
            this.PC_DlTimeSetBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_DlTimeSetBtn.BackgroundImage")));
            this.PC_DlTimeSetBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_DlTimeSetBtn.FlatAppearance.BorderSize = 0;
            this.PC_DlTimeSetBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_DlTimeSetBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_DlTimeSetBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_DlTimeSetBtn.Location = new System.Drawing.Point(362, 210);
            this.PC_DlTimeSetBtn.Name = "PC_DlTimeSetBtn";
            this.PC_DlTimeSetBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_DlTimeSetBtn.TabIndex = 0;
            this.PC_DlTimeSetBtn.Tag = "";
            this.PC_DlTimeSetBtn.UseVisualStyleBackColor = true;
            this.PC_DlTimeSetBtn.Click += new System.EventHandler(this.PC_DlTimeSetBtn_Click);
            // 
            // tabPageBed
            // 
            this.tabPageBed.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("tabPageBed.BackgroundImage")));
            this.tabPageBed.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPageBed.Controls.Add(this.pictureBox7);
            this.tabPageBed.Controls.Add(this.groupBox4);
            this.tabPageBed.Location = new System.Drawing.Point(4, 24);
            this.tabPageBed.Name = "tabPageBed";
            this.tabPageBed.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageBed.Size = new System.Drawing.Size(607, 450);
            this.tabPageBed.TabIndex = 3;
            this.tabPageBed.Tag = "0";
            this.tabPageBed.Text = "卧室灯";
            this.tabPageBed.UseVisualStyleBackColor = true;
            // 
            // pictureBox7
            // 
            this.pictureBox7.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox7.BackgroundImage")));
            this.pictureBox7.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox7.Location = new System.Drawing.Point(64, 10);
            this.pictureBox7.Name = "pictureBox7";
            this.pictureBox7.Size = new System.Drawing.Size(93, 70);
            this.pictureBox7.TabIndex = 6;
            this.pictureBox7.TabStop = false;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.UI_RlSetTimeListBox);
            this.groupBox4.Controls.Add(this.UI_RlSetTimeInfo);
            this.groupBox4.Controls.Add(this.label24);
            this.groupBox4.Controls.Add(this.label25);
            this.groupBox4.Controls.Add(this.UI_RlTimeSetHour);
            this.groupBox4.Controls.Add(this.UI_RlTimeSetMinute);
            this.groupBox4.Controls.Add(this.label22);
            this.groupBox4.Controls.Add(this.label23);
            this.groupBox4.Controls.Add(this.UI_RoomlightState2);
            this.groupBox4.Controls.Add(this.PC_RoomLightBtn);
            this.groupBox4.Controls.Add(this.PC_RlTimeCancelBtn);
            this.groupBox4.Controls.Add(this.PC_RlTimeSetBtn);
            this.groupBox4.Location = new System.Drawing.Point(53, 42);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(500, 350);
            this.groupBox4.TabIndex = 5;
            this.groupBox4.TabStop = false;
            // 
            // UI_RlSetTimeListBox
            // 
            this.UI_RlSetTimeListBox.BackColor = System.Drawing.SystemColors.Window;
            this.UI_RlSetTimeListBox.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_RlSetTimeListBox.ForeColor = System.Drawing.Color.DodgerBlue;
            this.UI_RlSetTimeListBox.FormattingEnabled = true;
            this.UI_RlSetTimeListBox.Items.AddRange(new object[] {
            "开",
            "关"});
            this.UI_RlSetTimeListBox.Location = new System.Drawing.Point(282, 213);
            this.UI_RlSetTimeListBox.Name = "UI_RlSetTimeListBox";
            this.UI_RlSetTimeListBox.Size = new System.Drawing.Size(42, 27);
            this.UI_RlSetTimeListBox.TabIndex = 19;
            // 
            // UI_RlSetTimeInfo
            // 
            this.UI_RlSetTimeInfo.AutoSize = true;
            this.UI_RlSetTimeInfo.Font = new System.Drawing.Font("华文新魏", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.UI_RlSetTimeInfo.ForeColor = System.Drawing.Color.AliceBlue;
            this.UI_RlSetTimeInfo.Location = new System.Drawing.Point(43, 273);
            this.UI_RlSetTimeInfo.Name = "UI_RlSetTimeInfo";
            this.UI_RlSetTimeInfo.Size = new System.Drawing.Size(104, 19);
            this.UI_RlSetTimeInfo.TabIndex = 12;
            this.UI_RlSetTimeInfo.Text = "　　无定时";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label24.ForeColor = System.Drawing.Color.AliceBlue;
            this.label24.Location = new System.Drawing.Point(128, 213);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(31, 26);
            this.label24.TabIndex = 10;
            this.label24.Text = "时";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label25.ForeColor = System.Drawing.Color.AliceBlue;
            this.label25.Location = new System.Drawing.Point(245, 212);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(31, 26);
            this.label25.TabIndex = 9;
            this.label25.Text = "分";
            // 
            // UI_RlTimeSetHour
            // 
            this.UI_RlTimeSetHour.Location = new System.Drawing.Point(47, 217);
            this.UI_RlTimeSetHour.MaxLength = 2;
            this.UI_RlTimeSetHour.Name = "UI_RlTimeSetHour";
            this.UI_RlTimeSetHour.Size = new System.Drawing.Size(73, 21);
            this.UI_RlTimeSetHour.TabIndex = 6;
            this.UI_RlTimeSetHour.Text = "0";
            this.UI_RlTimeSetHour.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_RlTimeSetHour_KeyPress);
            // 
            // UI_RlTimeSetMinute
            // 
            this.UI_RlTimeSetMinute.Location = new System.Drawing.Point(166, 217);
            this.UI_RlTimeSetMinute.MaxLength = 2;
            this.UI_RlTimeSetMinute.Name = "UI_RlTimeSetMinute";
            this.UI_RlTimeSetMinute.Size = new System.Drawing.Size(73, 21);
            this.UI_RlTimeSetMinute.TabIndex = 7;
            this.UI_RlTimeSetMinute.Text = "0";
            this.UI_RlTimeSetMinute.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_RlTimeSetMinute_KeyPress);
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label22.ForeColor = System.Drawing.Color.AliceBlue;
            this.label22.Location = new System.Drawing.Point(42, 75);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(117, 28);
            this.label22.TabIndex = 8;
            this.label22.Text = "开关设定：";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label23.ForeColor = System.Drawing.Color.AliceBlue;
            this.label23.Location = new System.Drawing.Point(42, 156);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(102, 28);
            this.label23.TabIndex = 7;
            this.label23.Text = "定时设定:";
            // 
            // UI_RoomlightState2
            // 
            this.UI_RoomlightState2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_RoomlightState2.BackgroundImage")));
            this.UI_RoomlightState2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_RoomlightState2.Location = new System.Drawing.Point(198, 75);
            this.UI_RoomlightState2.Name = "UI_RoomlightState2";
            this.UI_RoomlightState2.Size = new System.Drawing.Size(41, 39);
            this.UI_RoomlightState2.TabIndex = 4;
            this.UI_RoomlightState2.TabStop = false;
            // 
            // PC_RoomLightBtn
            // 
            this.PC_RoomLightBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_RoomLightBtn.BackgroundImage")));
            this.PC_RoomLightBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_RoomLightBtn.FlatAppearance.BorderSize = 0;
            this.PC_RoomLightBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_RoomLightBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_RoomLightBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_RoomLightBtn.Location = new System.Drawing.Point(297, 67);
            this.PC_RoomLightBtn.Name = "PC_RoomLightBtn";
            this.PC_RoomLightBtn.Size = new System.Drawing.Size(55, 52);
            this.PC_RoomLightBtn.TabIndex = 3;
            this.PC_RoomLightBtn.UseVisualStyleBackColor = true;
            this.PC_RoomLightBtn.Click += new System.EventHandler(this.PC_RoomLightBtn_Click);
            // 
            // PC_RlTimeCancelBtn
            // 
            this.PC_RlTimeCancelBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_RlTimeCancelBtn.BackgroundImage")));
            this.PC_RlTimeCancelBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_RlTimeCancelBtn.FlatAppearance.BorderSize = 0;
            this.PC_RlTimeCancelBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_RlTimeCancelBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_RlTimeCancelBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_RlTimeCancelBtn.Location = new System.Drawing.Point(362, 273);
            this.PC_RlTimeCancelBtn.Name = "PC_RlTimeCancelBtn";
            this.PC_RlTimeCancelBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_RlTimeCancelBtn.TabIndex = 1;
            this.PC_RlTimeCancelBtn.Tag = "";
            this.PC_RlTimeCancelBtn.UseVisualStyleBackColor = true;
            this.PC_RlTimeCancelBtn.Click += new System.EventHandler(this.PC_RlTimeCancelBtn_Click);
            // 
            // PC_RlTimeSetBtn
            // 
            this.PC_RlTimeSetBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_RlTimeSetBtn.BackgroundImage")));
            this.PC_RlTimeSetBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_RlTimeSetBtn.FlatAppearance.BorderSize = 0;
            this.PC_RlTimeSetBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_RlTimeSetBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_RlTimeSetBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_RlTimeSetBtn.Location = new System.Drawing.Point(362, 210);
            this.PC_RlTimeSetBtn.Name = "PC_RlTimeSetBtn";
            this.PC_RlTimeSetBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_RlTimeSetBtn.TabIndex = 0;
            this.PC_RlTimeSetBtn.Tag = "";
            this.PC_RlTimeSetBtn.UseVisualStyleBackColor = true;
            this.PC_RlTimeSetBtn.Click += new System.EventHandler(this.PC_RlTimeSetBtn_Click);
            // 
            // tabPageTime
            // 
            this.tabPageTime.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("tabPageTime.BackgroundImage")));
            this.tabPageTime.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPageTime.Controls.Add(this.pictureBox8);
            this.tabPageTime.Controls.Add(this.groupBox5);
            this.tabPageTime.ImageIndex = 2;
            this.tabPageTime.Location = new System.Drawing.Point(29, 4);
            this.tabPageTime.Name = "tabPageTime";
            this.tabPageTime.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageTime.Size = new System.Drawing.Size(611, 484);
            this.tabPageTime.TabIndex = 2;
            this.tabPageTime.Tag = "0";
            this.tabPageTime.Text = "时钟设置";
            this.tabPageTime.UseVisualStyleBackColor = true;
            // 
            // pictureBox8
            // 
            this.pictureBox8.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox8.BackgroundImage")));
            this.pictureBox8.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox8.Location = new System.Drawing.Point(76, 20);
            this.pictureBox8.Name = "pictureBox8";
            this.pictureBox8.Size = new System.Drawing.Size(80, 72);
            this.pictureBox8.TabIndex = 1;
            this.pictureBox8.TabStop = false;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.PC_SendTimeBtn);
            this.groupBox5.Controls.Add(this.label32);
            this.groupBox5.Controls.Add(this.label31);
            this.groupBox5.Controls.Add(this.UI_SetMinute);
            this.groupBox5.Controls.Add(this.UI_SetHour);
            this.groupBox5.Controls.Add(this.PC_DateTimeSetBtn);
            this.groupBox5.Controls.Add(this.label28);
            this.groupBox5.Controls.Add(this.label27);
            this.groupBox5.Controls.Add(this.label26);
            this.groupBox5.Controls.Add(this.UI_SetDay);
            this.groupBox5.Controls.Add(this.UI_SetMonth);
            this.groupBox5.Controls.Add(this.UI_SetYear);
            this.groupBox5.Controls.Add(this.label30);
            this.groupBox5.Controls.Add(this.label29);
            this.groupBox5.Location = new System.Drawing.Point(60, 44);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(493, 363);
            this.groupBox5.TabIndex = 0;
            this.groupBox5.TabStop = false;
            // 
            // PC_SendTimeBtn
            // 
            this.PC_SendTimeBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_SendTimeBtn.BackgroundImage")));
            this.PC_SendTimeBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_SendTimeBtn.FlatAppearance.BorderSize = 0;
            this.PC_SendTimeBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_SendTimeBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_SendTimeBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_SendTimeBtn.Location = new System.Drawing.Point(331, 37);
            this.PC_SendTimeBtn.Name = "PC_SendTimeBtn";
            this.PC_SendTimeBtn.Size = new System.Drawing.Size(133, 49);
            this.PC_SendTimeBtn.TabIndex = 14;
            this.PC_SendTimeBtn.UseVisualStyleBackColor = true;
            this.PC_SendTimeBtn.Click += new System.EventHandler(this.PC_SendTimeBtn_Click);
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label32.ForeColor = System.Drawing.Color.AliceBlue;
            this.label32.Location = new System.Drawing.Point(242, 275);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(32, 27);
            this.label32.TabIndex = 12;
            this.label32.Text = "分";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label31.ForeColor = System.Drawing.Color.AliceBlue;
            this.label31.Location = new System.Drawing.Point(119, 275);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(32, 27);
            this.label31.TabIndex = 11;
            this.label31.Text = "时";
            // 
            // UI_SetMinute
            // 
            this.UI_SetMinute.Location = new System.Drawing.Point(155, 275);
            this.UI_SetMinute.MaxLength = 2;
            this.UI_SetMinute.Name = "UI_SetMinute";
            this.UI_SetMinute.Size = new System.Drawing.Size(81, 21);
            this.UI_SetMinute.TabIndex = 10;
            this.UI_SetMinute.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_SetMinute_KeyPress);
            // 
            // UI_SetHour
            // 
            this.UI_SetHour.Location = new System.Drawing.Point(33, 275);
            this.UI_SetHour.MaxLength = 2;
            this.UI_SetHour.Name = "UI_SetHour";
            this.UI_SetHour.Size = new System.Drawing.Size(81, 21);
            this.UI_SetHour.TabIndex = 9;
            this.UI_SetHour.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_SetHour_KeyPress);
            // 
            // PC_DateTimeSetBtn
            // 
            this.PC_DateTimeSetBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("PC_DateTimeSetBtn.BackgroundImage")));
            this.PC_DateTimeSetBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.PC_DateTimeSetBtn.FlatAppearance.BorderSize = 0;
            this.PC_DateTimeSetBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PC_DateTimeSetBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PC_DateTimeSetBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PC_DateTimeSetBtn.Location = new System.Drawing.Point(340, 265);
            this.PC_DateTimeSetBtn.Name = "PC_DateTimeSetBtn";
            this.PC_DateTimeSetBtn.Size = new System.Drawing.Size(91, 39);
            this.PC_DateTimeSetBtn.TabIndex = 8;
            this.PC_DateTimeSetBtn.Tag = "";
            this.PC_DateTimeSetBtn.UseVisualStyleBackColor = true;
            this.PC_DateTimeSetBtn.Click += new System.EventHandler(this.PC_DateTimeSetBtn_Click);
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label28.ForeColor = System.Drawing.Color.AliceBlue;
            this.label28.Location = new System.Drawing.Point(368, 153);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(32, 27);
            this.label28.TabIndex = 7;
            this.label28.Text = "日";
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label27.ForeColor = System.Drawing.Color.AliceBlue;
            this.label27.Location = new System.Drawing.Point(242, 153);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(32, 27);
            this.label27.TabIndex = 6;
            this.label27.Text = "月";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Font = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label26.ForeColor = System.Drawing.Color.AliceBlue;
            this.label26.Location = new System.Drawing.Point(119, 153);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(32, 27);
            this.label26.TabIndex = 5;
            this.label26.Text = "年";
            // 
            // UI_SetDay
            // 
            this.UI_SetDay.Location = new System.Drawing.Point(281, 153);
            this.UI_SetDay.MaxLength = 2;
            this.UI_SetDay.Name = "UI_SetDay";
            this.UI_SetDay.Size = new System.Drawing.Size(81, 21);
            this.UI_SetDay.TabIndex = 4;
            this.UI_SetDay.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_SetDay_KeyPress);
            // 
            // UI_SetMonth
            // 
            this.UI_SetMonth.Location = new System.Drawing.Point(155, 153);
            this.UI_SetMonth.MaxLength = 2;
            this.UI_SetMonth.Name = "UI_SetMonth";
            this.UI_SetMonth.Size = new System.Drawing.Size(81, 21);
            this.UI_SetMonth.TabIndex = 3;
            this.UI_SetMonth.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_SetMonth_KeyPress);
            // 
            // UI_SetYear
            // 
            this.UI_SetYear.Location = new System.Drawing.Point(33, 153);
            this.UI_SetYear.MaxLength = 4;
            this.UI_SetYear.Name = "UI_SetYear";
            this.UI_SetYear.Size = new System.Drawing.Size(81, 21);
            this.UI_SetYear.TabIndex = 2;
            this.UI_SetYear.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.UI_SetYear_KeyPress);
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label30.ForeColor = System.Drawing.Color.AliceBlue;
            this.label30.Location = new System.Drawing.Point(27, 215);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(117, 28);
            this.label30.TabIndex = 1;
            this.label30.Text = "时间设定：";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label29.ForeColor = System.Drawing.Color.AliceBlue;
            this.label29.Location = new System.Drawing.Point(27, 95);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(117, 28);
            this.label29.TabIndex = 0;
            this.label29.Text = "日期设定：";
            // 
            // tabPageMode
            // 
            this.tabPageMode.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("tabPageMode.BackgroundImage")));
            this.tabPageMode.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPageMode.Controls.Add(this.groupBox6);
            this.tabPageMode.ImageIndex = 3;
            this.tabPageMode.Location = new System.Drawing.Point(29, 4);
            this.tabPageMode.Name = "tabPageMode";
            this.tabPageMode.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageMode.Size = new System.Drawing.Size(611, 484);
            this.tabPageMode.TabIndex = 3;
            this.tabPageMode.Tag = "0";
            this.tabPageMode.Text = "模式选择";
            this.tabPageMode.UseVisualStyleBackColor = true;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.pictureBox12);
            this.groupBox6.Controls.Add(this.pictureBox11);
            this.groupBox6.Controls.Add(this.pictureBox10);
            this.groupBox6.Controls.Add(this.pictureBox9);
            this.groupBox6.Controls.Add(this.label36);
            this.groupBox6.Controls.Add(this.label35);
            this.groupBox6.Controls.Add(this.label34);
            this.groupBox6.Controls.Add(this.label33);
            this.groupBox6.Controls.Add(this.PC_NormalMode);
            this.groupBox6.Controls.Add(this.PC_GoHomeMode);
            this.groupBox6.Controls.Add(this.PC_OutMode);
            this.groupBox6.Controls.Add(this.PC_AntiThiefMode);
            this.groupBox6.Font = new System.Drawing.Font("华文新魏", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox6.ForeColor = System.Drawing.Color.AliceBlue;
            this.groupBox6.Location = new System.Drawing.Point(36, 26);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(540, 406);
            this.groupBox6.TabIndex = 0;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "环境模式";
            // 
            // pictureBox12
            // 
            this.pictureBox12.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox12.BackgroundImage")));
            this.pictureBox12.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox12.Location = new System.Drawing.Point(13, 287);
            this.pictureBox12.Name = "pictureBox12";
            this.pictureBox12.Size = new System.Drawing.Size(46, 39);
            this.pictureBox12.TabIndex = 12;
            this.pictureBox12.TabStop = false;
            // 
            // pictureBox11
            // 
            this.pictureBox11.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox11.BackgroundImage")));
            this.pictureBox11.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox11.Location = new System.Drawing.Point(13, 220);
            this.pictureBox11.Name = "pictureBox11";
            this.pictureBox11.Size = new System.Drawing.Size(46, 39);
            this.pictureBox11.TabIndex = 11;
            this.pictureBox11.TabStop = false;
            // 
            // pictureBox10
            // 
            this.pictureBox10.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox10.BackgroundImage")));
            this.pictureBox10.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox10.Location = new System.Drawing.Point(13, 148);
            this.pictureBox10.Name = "pictureBox10";
            this.pictureBox10.Size = new System.Drawing.Size(46, 39);
            this.pictureBox10.TabIndex = 10;
            this.pictureBox10.TabStop = false;
            // 
            // pictureBox9
            // 
            this.pictureBox9.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox9.BackgroundImage")));
            this.pictureBox9.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox9.Location = new System.Drawing.Point(13, 78);
            this.pictureBox9.Name = "pictureBox9";
            this.pictureBox9.Size = new System.Drawing.Size(46, 39);
            this.pictureBox9.TabIndex = 9;
            this.pictureBox9.TabStop = false;
            // 
            // label36
            // 
            this.label36.AutoSize = true;
            this.label36.Font = new System.Drawing.Font("华文新魏", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label36.Location = new System.Drawing.Point(215, 295);
            this.label36.Name = "label36";
            this.label36.Size = new System.Drawing.Size(328, 85);
            this.label36.TabIndex = 8;
            this.label36.Text = "模式说明：系统进入此模式，开启小偷检测，\r\n\r\n　　　　　当小偷来临时报警（用于用户在\r\n　　　　\r\n　　　　　家时使用）";
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Font = new System.Drawing.Font("华文新魏", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label35.Location = new System.Drawing.Point(215, 228);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(328, 51);
            this.label35.TabIndex = 7;
            this.label35.Text = "模式说明：系统进入此模式，所有电器关闭，\r\n　\r\n　　　　　同时开启防盗模式";
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Font = new System.Drawing.Font("华文新魏", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label34.Location = new System.Drawing.Point(215, 156);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(328, 51);
            this.label34.TabIndex = 6;
            this.label34.Text = "模式说明：系统进入此模式，自动开启电灯、\r\n　　　　　　\r\n　　　　　热水器、空调等家电";
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Font = new System.Drawing.Font("华文新魏", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label33.Location = new System.Drawing.Point(215, 86);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(312, 51);
            this.label33.TabIndex = 5;
            this.label33.Text = "模式说明：系统进入此模式，不进行个性化\r\n\r\n　　　　　设定，电器状态由用户自行改变";
            // 
            // PC_NormalMode
            // 
            this.PC_NormalMode.AutoSize = true;
            this.PC_NormalMode.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.PC_NormalMode.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.PC_NormalMode.Location = new System.Drawing.Point(70, 78);
            this.PC_NormalMode.Name = "PC_NormalMode";
            this.PC_NormalMode.Size = new System.Drawing.Size(114, 32);
            this.PC_NormalMode.TabIndex = 1;
            this.PC_NormalMode.TabStop = true;
            this.PC_NormalMode.Text = "普通模式";
            this.PC_NormalMode.UseVisualStyleBackColor = true;
            this.PC_NormalMode.Click += new System.EventHandler(this.PC_NormalMode_Click);
            // 
            // PC_GoHomeMode
            // 
            this.PC_GoHomeMode.AutoSize = true;
            this.PC_GoHomeMode.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.PC_GoHomeMode.Location = new System.Drawing.Point(70, 148);
            this.PC_GoHomeMode.Name = "PC_GoHomeMode";
            this.PC_GoHomeMode.Size = new System.Drawing.Size(114, 32);
            this.PC_GoHomeMode.TabIndex = 2;
            this.PC_GoHomeMode.TabStop = true;
            this.PC_GoHomeMode.Text = "回家模式";
            this.PC_GoHomeMode.UseVisualStyleBackColor = true;
            this.PC_GoHomeMode.Click += new System.EventHandler(this.PC_GoHomeMode_Click);
            // 
            // PC_OutMode
            // 
            this.PC_OutMode.AutoSize = true;
            this.PC_OutMode.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.PC_OutMode.Location = new System.Drawing.Point(70, 220);
            this.PC_OutMode.Name = "PC_OutMode";
            this.PC_OutMode.Size = new System.Drawing.Size(114, 32);
            this.PC_OutMode.TabIndex = 3;
            this.PC_OutMode.TabStop = true;
            this.PC_OutMode.Text = "外出模式";
            this.PC_OutMode.UseVisualStyleBackColor = true;
            this.PC_OutMode.Click += new System.EventHandler(this.PC_OutMode_Click);
            // 
            // PC_AntiThiefMode
            // 
            this.PC_AntiThiefMode.AutoSize = true;
            this.PC_AntiThiefMode.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.PC_AntiThiefMode.Location = new System.Drawing.Point(70, 287);
            this.PC_AntiThiefMode.Name = "PC_AntiThiefMode";
            this.PC_AntiThiefMode.Size = new System.Drawing.Size(114, 32);
            this.PC_AntiThiefMode.TabIndex = 4;
            this.PC_AntiThiefMode.TabStop = true;
            this.PC_AntiThiefMode.Text = "防盗模式";
            this.PC_AntiThiefMode.UseVisualStyleBackColor = true;
            this.PC_AntiThiefMode.Click += new System.EventHandler(this.PC_AntiThiefMode_Click);
            // 
            // tabPageHelp
            // 
            this.tabPageHelp.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("tabPageHelp.BackgroundImage")));
            this.tabPageHelp.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPageHelp.Controls.Add(this.groupBox8);
            this.tabPageHelp.Controls.Add(this.groupBox7);
            this.tabPageHelp.ImageIndex = 4;
            this.tabPageHelp.Location = new System.Drawing.Point(29, 4);
            this.tabPageHelp.Name = "tabPageHelp";
            this.tabPageHelp.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageHelp.Size = new System.Drawing.Size(611, 484);
            this.tabPageHelp.TabIndex = 4;
            this.tabPageHelp.Tag = "0";
            this.tabPageHelp.Text = "帮助";
            this.tabPageHelp.UseVisualStyleBackColor = true;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.label42);
            this.groupBox8.Font = new System.Drawing.Font("华文新魏", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox8.ForeColor = System.Drawing.Color.AliceBlue;
            this.groupBox8.Location = new System.Drawing.Point(61, 246);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(488, 187);
            this.groupBox8.TabIndex = 1;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "关于我们";
            // 
            // label42
            // 
            this.label42.AutoSize = true;
            this.label42.Font = new System.Drawing.Font("华文新魏", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label42.Location = new System.Drawing.Point(9, 42);
            this.label42.Name = "label42";
            this.label42.Size = new System.Drawing.Size(472, 34);
            this.label42.TabIndex = 0;
            this.label42.Text = "开发团队：南蛮入侵\r\n开发人员：潘维、程敏、杨林龙、林雨根、林鹏、汤文兵、姜玲颖";
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.label40);
            this.groupBox7.Font = new System.Drawing.Font("华文新魏", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox7.ForeColor = System.Drawing.Color.AliceBlue;
            this.groupBox7.Location = new System.Drawing.Point(62, 27);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(488, 203);
            this.groupBox7.TabIndex = 0;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "帮助";
            // 
            // label40
            // 
            this.label40.AutoSize = true;
            this.label40.Font = new System.Drawing.Font("华文新魏", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label40.Location = new System.Drawing.Point(14, 36);
            this.label40.Name = "label40";
            this.label40.Size = new System.Drawing.Size(462, 133);
            this.label40.TabIndex = 0;
            this.label40.Text = "本产品旨在方便用户对家电的的智能化管理。\r\n主要功能有：\r\n1.对家电开关，空调、热水器温度等信息状态的显示；\r\n2.关于家电开关的设置，空调、热水器温度的设置；" +
                "\r\n3.可通过手动和自动获取电脑时间同步下位机端时间；\r\n4.提供四种环境模式，方便用户根据各自不同的需求来\r\n　选择。";
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "状态信息.png");
            this.imageList1.Images.SetKeyName(1, "电器控制.png");
            this.imageList1.Images.SetKeyName(2, "时钟.png");
            this.imageList1.Images.SetKeyName(3, "模式选择.png");
            this.imageList1.Images.SetKeyName(4, "帮助.png");
            // 
            // imageList2
            // 
            this.imageList2.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList2.ImageStream")));
            this.imageList2.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList2.Images.SetKeyName(0, "绿灯.png");
            this.imageList2.Images.SetKeyName(1, "灰灯.png");
            this.imageList2.Images.SetKeyName(2, "红灯.png");
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.PC_timer1_Tick);
            // 
            // timer2
            // 
            this.timer2.Interval = 1000;
            this.timer2.Tick += new System.EventHandler(this.PC_timer2_Tick);
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.ContextMenuStrip = this.contextMenuStrip1;
            this.notifyIcon1.Text = "智能家电控制系统";
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.PC_notifyIcon1_MouseDoubleClick);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.显示ToolStripMenuItem,
            this.退出ToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(99, 48);
            // 
            // 显示ToolStripMenuItem
            // 
            this.显示ToolStripMenuItem.Name = "显示ToolStripMenuItem";
            this.显示ToolStripMenuItem.Size = new System.Drawing.Size(98, 22);
            this.显示ToolStripMenuItem.Text = "显示";
            this.显示ToolStripMenuItem.Click += new System.EventHandler(this.PC_ShowToolStripMenuItem_Click);
            // 
            // 退出ToolStripMenuItem
            // 
            this.退出ToolStripMenuItem.Name = "退出ToolStripMenuItem";
            this.退出ToolStripMenuItem.Size = new System.Drawing.Size(98, 22);
            this.退出ToolStripMenuItem.Text = "退出";
            this.退出ToolStripMenuItem.Click += new System.EventHandler(this.PC_ExitToolStripMenuItem_Click);
            // 
            // serialport
            // 
            this.serialport.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.PC_serialPort_DataReceived);
            // 
            // PC_DlTimer
            // 
            this.PC_DlTimer.Interval = 1000;
            this.PC_DlTimer.Tick += new System.EventHandler(this.PC_DlTimer_Tick);
            // 
            // PC_RlTimer
            // 
            this.PC_RlTimer.Interval = 1000;
            this.PC_RlTimer.Tick += new System.EventHandler(this.PC_RlTimer_Tick);
            // 
            // PC_WhTimer
            // 
            this.PC_WhTimer.Interval = 1000;
            this.PC_WhTimer.Tick += new System.EventHandler(this.PC_WhTimer_Tick);
            // 
            // PC_AcTimer
            // 
            this.PC_AcTimer.Interval = 1000;
            this.PC_AcTimer.Tick += new System.EventHandler(this.PC_AcTimer_Tick);
            // 
            // FormUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(642, 477);
            this.Controls.Add(this.tabControl1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(650, 510);
            this.MinimumSize = new System.Drawing.Size(650, 510);
            this.Name = "FormUI";
            this.Text = "智能家电控制系统";
            this.Resize += new System.EventHandler(this.PC_FormUI_Resize);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PC_FormUI_FormClosing);
            this.Load += new System.EventHandler(this.PC_FormUI_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPageInfo.ResumeLayout(false);
            this.tabPageInfo.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_PoliceState)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.UI_RoomlightState1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.UI_WaterheaterState1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.UI_DoorlightState1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.UI_AirconditionState1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxPolic)).EndInit();
            this.groupBoxData.ResumeLayout(false);
            this.groupBoxData.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.tabPageControl.ResumeLayout(false);
            this.tabControl2.ResumeLayout(false);
            this.tabPageAir.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_AirconditionState2)).EndInit();
            this.tabPageHot.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_WaterheaterState2)).EndInit();
            this.tabPageDoor.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox6)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_DoorlightState2)).EndInit();
            this.tabPageBed.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox7)).EndInit();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UI_RoomlightState2)).EndInit();
            this.tabPageTime.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox8)).EndInit();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.tabPageMode.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox12)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox11)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox10)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox9)).EndInit();
            this.tabPageHelp.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private Sunisoft.IrisSkin.SkinEngine skinEngineUI;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPageControl;
        private System.Windows.Forms.TabPage tabPageTime;
        private System.Windows.Forms.TabPage tabPageMode;
        private System.Windows.Forms.TabPage tabPageHelp;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TabPage tabPageAir;
        private System.Windows.Forms.TabPage tabPageHot;
        private System.Windows.Forms.TabPage tabPageDoor;
        private System.Windows.Forms.TabPage tabPageBed;
        private System.Windows.Forms.TabPage tabPageInfo;
        private System.Windows.Forms.Button UI_WaterHeaterBtn;
        private System.Windows.Forms.Button UI_RoomLightBtn;
        private System.Windows.Forms.PictureBox pictureBoxPolic;
        private System.Windows.Forms.Button UI_DoorLightBtn;
        private System.Windows.Forms.GroupBox groupBoxData;
        private System.Windows.Forms.Label UI_labelConnect;
        private System.Windows.Forms.Label UI_labelLight;
        private System.Windows.Forms.Label UI_labelTemp;
        private System.Windows.Forms.Label labelDate;
        private System.Windows.Forms.Label labelTime;
        private System.Windows.Forms.Button UI_AirConditionBtn;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button PC_buttonUpdate;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.PictureBox UI_AirconditionState1;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.PictureBox UI_DoorlightState1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label UI_Alarm;
        private System.Windows.Forms.PictureBox UI_PoliceState;
        private System.Windows.Forms.PictureBox UI_RoomlightState1;
        private System.Windows.Forms.PictureBox UI_WaterheaterState1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox UI_WhTimeSetHour;
        private System.Windows.Forms.TextBox UI_WhTimeSetMinute;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox UI_WhTempSet;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.PictureBox UI_WaterheaterState2;
        private System.Windows.Forms.Button PC_WaterHeaterBtn;
        private System.Windows.Forms.Button PC_WhTempSetBtn;
        private System.Windows.Forms.Button PC_WhTimeCancelBtn;
        private System.Windows.Forms.Button PC_WhTimeSetBtn;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.TextBox UI_RlTimeSetHour;
        private System.Windows.Forms.TextBox UI_RlTimeSetMinute;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.PictureBox UI_RoomlightState2;
        private System.Windows.Forms.Button PC_RoomLightBtn;
        private System.Windows.Forms.Button PC_RlTimeCancelBtn;
        private System.Windows.Forms.Button PC_RlTimeSetBtn;
        private System.Windows.Forms.PictureBox pictureBox5;
        private System.Windows.Forms.PictureBox pictureBox6;
        private System.Windows.Forms.PictureBox pictureBox7;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label0;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox UI_AcTimeSetHour;
        private System.Windows.Forms.TextBox UI_AcTimeSetMinute;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox UI_AcTempSet;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.PictureBox UI_AirconditionState2;
        private System.Windows.Forms.Button PC_AirConditionBtn;
        private System.Windows.Forms.Button PC_AcTempSetBtn;
        private System.Windows.Forms.Button PC_AcTimeCancelBtn;
        private System.Windows.Forms.Button PC_AcTimeSetBtn;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.TextBox UI_SetMinute;
        private System.Windows.Forms.TextBox UI_SetHour;
        private System.Windows.Forms.Button PC_DateTimeSetBtn;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.TextBox UI_SetDay;
        private System.Windows.Forms.TextBox UI_SetMonth;
        private System.Windows.Forms.TextBox UI_SetYear;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.PictureBox UI_DoorlightState2;
        private System.Windows.Forms.Button PC_DoorLightBtn;
        private System.Windows.Forms.RadioButton PC_NormalMode;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.RadioButton PC_GoHomeMode;
        private System.Windows.Forms.RadioButton PC_OutMode;
        private System.Windows.Forms.RadioButton PC_AntiThiefMode;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.Label label36;
        private System.Windows.Forms.Label label35;
        private System.Windows.Forms.Button PC_SendTimeBtn;
        private System.Windows.Forms.Label labelWeek;
        private System.Windows.Forms.PictureBox pictureBox8;
        private System.Windows.Forms.PictureBox pictureBox9;
        private System.Windows.Forms.PictureBox pictureBox10;
        private System.Windows.Forms.PictureBox pictureBox12;
        private System.Windows.Forms.PictureBox pictureBox11;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.ImageList imageList2;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 显示ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出ToolStripMenuItem;
        private System.IO.Ports.SerialPort serialport;
        private System.IO.Ports.SerialPort serialPort1;
        private Label UI_AcSetTimeInfo;
        private Label UI_WhSetTimeInfo;
        private Label UI_RlSetTimeInfo;
        private Label UI_labelWhInfo;
        private Label UI_labelRlInfo;
        private Label UI_labelAcInfo;
        private Label UI_labelMode;
        private Label UI_labelDlInfo;
        private GroupBox groupBox3;
        private Label UI_DlSetTimeInfo;
        private Label label20;
        private Label label21;
        private TextBox UI_DlTimeSetHour;
        private TextBox UI_DlTimeSetMinute;
        private Label label18;
        private Label label19;
        private Button PC_DlTimeCancelBtn;
        private Button PC_DlTimeSetBtn;
        private Timer PC_DlTimer;
        private Timer PC_RlTimer;
        private Timer PC_WhTimer;
        private Label UI_labelAcTemp;
        private Label label37;
        private Label UI_labelWhTemp;
        private Label label38;
        private Label label39;
        private Label UI_AcSetTempInfo;
        private Label UI_WhSetTempInfo;
        private Label label41;
        private ComboBox UI_AcSetTimeComboBox;
        private ComboBox UI_WhSetTimeListBox;
        private ComboBox UI_DlSetTimeListBox;
        private ComboBox UI_RlSetTimeListBox;
        private GroupBox groupBox8;
        private GroupBox groupBox7;
        private Label label42;
        private Label label40;
        private TextBox PC_Unshow;
        public Timer PC_AcTimer;
    }
}

