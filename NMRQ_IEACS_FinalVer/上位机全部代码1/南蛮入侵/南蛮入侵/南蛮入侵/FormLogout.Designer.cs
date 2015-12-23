namespace 南蛮入侵
{
    partial class FormLogout
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

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormLogout));
            this.skinEngine1 = new Sunisoft.IrisSkin.SkinEngine(((System.ComponentModel.Component)(this)));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.UI_LogoutCancelBtn = new System.Windows.Forms.Button();
            this.UI_LogoutBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // skinEngine1
            // 
            this.skinEngine1.DisableTag = 0;
            this.skinEngine1.SerialNumber = "";
            this.skinEngine1.SkinFile = null;
            this.skinEngine1.SkinStreamMain = ((System.IO.Stream)(resources.GetObject("skinEngine1.SkinStreamMain")));
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Transparent;
            this.groupBox1.Controls.Add(this.UI_LogoutCancelBtn);
            this.groupBox1.Controls.Add(this.UI_LogoutBtn);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupBox1.Location = new System.Drawing.Point(37, 33);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(219, 150);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Tag = "0";
            // 
            // UI_LogoutCancelBtn
            // 
            this.UI_LogoutCancelBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_LogoutCancelBtn.BackgroundImage")));
            this.UI_LogoutCancelBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_LogoutCancelBtn.FlatAppearance.BorderSize = 0;
            this.UI_LogoutCancelBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.UI_LogoutCancelBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.UI_LogoutCancelBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.UI_LogoutCancelBtn.Location = new System.Drawing.Point(126, 96);
            this.UI_LogoutCancelBtn.Name = "UI_LogoutCancelBtn";
            this.UI_LogoutCancelBtn.Size = new System.Drawing.Size(65, 32);
            this.UI_LogoutCancelBtn.TabIndex = 2;
            this.UI_LogoutCancelBtn.Tag = "0";
            this.UI_LogoutCancelBtn.UseVisualStyleBackColor = true;
            this.UI_LogoutCancelBtn.Click += new System.EventHandler(this.UI_LogoutCancelBtn_Click);
            // 
            // UI_LogoutBtn
            // 
            this.UI_LogoutBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("UI_LogoutBtn.BackgroundImage")));
            this.UI_LogoutBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UI_LogoutBtn.FlatAppearance.BorderSize = 0;
            this.UI_LogoutBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.UI_LogoutBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.UI_LogoutBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.UI_LogoutBtn.Location = new System.Drawing.Point(30, 96);
            this.UI_LogoutBtn.Name = "UI_LogoutBtn";
            this.UI_LogoutBtn.Size = new System.Drawing.Size(65, 32);
            this.UI_LogoutBtn.TabIndex = 1;
            this.UI_LogoutBtn.Tag = "0";
            this.UI_LogoutBtn.UseVisualStyleBackColor = true;
            this.UI_LogoutBtn.Click += new System.EventHandler(this.UI_LogoutBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.ForeColor = System.Drawing.Color.AliceBlue;
            this.label1.Location = new System.Drawing.Point(46, 52);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(145, 26);
            this.label1.TabIndex = 0;
            this.label1.Tag = "0";
            this.label1.Text = "是否退出系统？";
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.Transparent;
            this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox1.Location = new System.Drawing.Point(51, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(48, 55);
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Tag = "0";
            // 
            // FormLogout
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(292, 226);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(300, 260);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(300, 260);
            this.Name = "FormLogout";
            this.Text = "退出系统";
            this.Load += new System.EventHandler(this.FormLogout_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private Sunisoft.IrisSkin.SkinEngine skinEngine1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button UI_LogoutCancelBtn;
        private System.Windows.Forms.Button UI_LogoutBtn;
    }
}