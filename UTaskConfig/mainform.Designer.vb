<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Public Class mainform
	Inherits System.Windows.Forms.Form

	'Form overrides dispose to clean up the component list.
	<System.Diagnostics.DebuggerNonUserCode()> _
	Protected Overrides Sub Dispose(ByVal disposing As Boolean)
		If disposing AndAlso components IsNot Nothing Then
			components.Dispose()
		End If
		MyBase.Dispose(disposing)
	End Sub

	'Required by the Windows Form Designer
	Private components As System.ComponentModel.IContainer
	Private mainMenu1 As System.Windows.Forms.MainMenu

	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.  
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> _
	Private Sub InitializeComponent()
		Me.mainMenu1 = New System.Windows.Forms.MainMenu
		Me.menuCancel = New System.Windows.Forms.MenuItem
		Me.menuSave = New System.Windows.Forms.MenuItem
		Me.TabControl1 = New System.Windows.Forms.TabControl
		Me.KeysTab = New System.Windows.Forms.TabPage
		Me.btnGoToConfigure = New System.Windows.Forms.Button
		Me.lbKeys = New System.Windows.Forms.ListBox
		Me.lblChooseKeyFromList = New System.Windows.Forms.Label
		Me.PictureBox2 = New System.Windows.Forms.PictureBox
		Me.KeyConfigTab = New System.Windows.Forms.TabPage
		Me.chkVibraEnabled = New System.Windows.Forms.CheckBox
		Me.lblTime = New System.Windows.Forms.Label
		Me.btnBrowse = New System.Windows.Forms.Button
		Me.lblArguments = New System.Windows.Forms.Label
		Me.lblFile = New System.Windows.Forms.Label
		Me.txtArgs = New System.Windows.Forms.TextBox
		Me.txtPath = New System.Windows.Forms.TextBox
		Me.btnGoToKeysList = New System.Windows.Forms.Button
		Me.lblConfigureKeyHeader = New System.Windows.Forms.Label
		Me.intVibraTime = New System.Windows.Forms.TextBox
		Me.rbtnMinimize = New System.Windows.Forms.RadioButton
		Me.rbtnClose = New System.Windows.Forms.RadioButton
		Me.rbtnExecute = New System.Windows.Forms.RadioButton
		Me.rbtnStandard = New System.Windows.Forms.RadioButton
		Me.PictureBox1 = New System.Windows.Forms.PictureBox
		Me.rbtnStartMenu = New System.Windows.Forms.RadioButton
		Me.GlobalTab = New System.Windows.Forms.TabPage
		Me.chkEnableService = New System.Windows.Forms.CheckBox
		Me.chkHookTaskBar = New System.Windows.Forms.CheckBox
		Me.chkEnhanceToolbarWindows = New System.Windows.Forms.CheckBox
		Me.lblGlobalSettings = New System.Windows.Forms.Label
		Me.PictureBox3 = New System.Windows.Forms.PictureBox
		Me.chkHomeIcon = New System.Windows.Forms.CheckBox
		Me.chkLongPressAnimation = New System.Windows.Forms.CheckBox
		Me.TodayWindowsTab = New System.Windows.Forms.TabPage
		Me.btnClasses = New System.Windows.Forms.Button
		Me.txtTodayWindows = New System.Windows.Forms.TextBox
		Me.lblTodayClasses = New System.Windows.Forms.Label
		Me.ExceptionsTab = New System.Windows.Forms.TabPage
		Me.txtExceptions = New System.Windows.Forms.TextBox
		Me.lblExceptions = New System.Windows.Forms.Label
		Me.PositionFixTab = New System.Windows.Forms.TabPage
		Me.btnClasses2 = New System.Windows.Forms.Button
		Me.chkPositionFixAuto = New System.Windows.Forms.CheckBox
		Me.chkPositionFixEnable = New System.Windows.Forms.CheckBox
		Me.lblPositionFixWarn = New System.Windows.Forms.Label
		Me.txtPosFixNoFix = New System.Windows.Forms.TextBox
		Me.txtPosFixToFix = New System.Windows.Forms.TextBox
		Me.TabControl1.SuspendLayout()
		Me.KeysTab.SuspendLayout()
		Me.KeyConfigTab.SuspendLayout()
		Me.GlobalTab.SuspendLayout()
		Me.TodayWindowsTab.SuspendLayout()
		Me.ExceptionsTab.SuspendLayout()
		Me.PositionFixTab.SuspendLayout()
		Me.SuspendLayout()
		'
		'mainMenu1
		'
		Me.mainMenu1.MenuItems.Add(Me.menuCancel)
		Me.mainMenu1.MenuItems.Add(Me.menuSave)
		'
		'menuCancel
		'
		Me.menuCancel.Text = "Cancel"
		'
		'menuSave
		'
		Me.menuSave.Text = "Save"
		'
		'TabControl1
		'
		Me.TabControl1.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
					Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.TabControl1.Controls.Add(Me.KeysTab)
		Me.TabControl1.Controls.Add(Me.KeyConfigTab)
		Me.TabControl1.Controls.Add(Me.GlobalTab)
		Me.TabControl1.Controls.Add(Me.TodayWindowsTab)
		Me.TabControl1.Controls.Add(Me.ExceptionsTab)
		Me.TabControl1.Controls.Add(Me.PositionFixTab)
		Me.TabControl1.Dock = System.Windows.Forms.DockStyle.None
		Me.TabControl1.Font = New System.Drawing.Font("Tahoma", 10.0!, System.Drawing.FontStyle.Regular)
		Me.TabControl1.Location = New System.Drawing.Point(0, 0)
		Me.TabControl1.Name = "TabControl1"
		Me.TabControl1.SelectedIndex = 0
		Me.TabControl1.Size = New System.Drawing.Size(240, 268)
		Me.TabControl1.TabIndex = 1
		'
		'KeysTab
		'
		Me.KeysTab.Controls.Add(Me.btnGoToConfigure)
		Me.KeysTab.Controls.Add(Me.lbKeys)
		Me.KeysTab.Controls.Add(Me.lblChooseKeyFromList)
		Me.KeysTab.Controls.Add(Me.PictureBox2)
		Me.KeysTab.Location = New System.Drawing.Point(0, 0)
		Me.KeysTab.Name = "KeysTab"
		Me.KeysTab.Size = New System.Drawing.Size(240, 241)
		Me.KeysTab.Text = "Keys"
		'
		'btnGoToConfigure
		'
		Me.btnGoToConfigure.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.btnGoToConfigure.BackColor = System.Drawing.Color.Gainsboro
		Me.btnGoToConfigure.Location = New System.Drawing.Point(170, 3)
		Me.btnGoToConfigure.Name = "btnGoToConfigure"
		Me.btnGoToConfigure.Size = New System.Drawing.Size(60, 24)
		Me.btnGoToConfigure.TabIndex = 10
		Me.btnGoToConfigure.Text = ">>"
		'
		'lbKeys
		'
		Me.lbKeys.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
					Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lbKeys.Font = New System.Drawing.Font("Tahoma", 12.0!, System.Drawing.FontStyle.Regular)
		Me.lbKeys.Items.Add("""Windows"" key")
		Me.lbKeys.Items.Add("""Windows"" key (long press)")
		Me.lbKeys.Items.Add("Close key")
		Me.lbKeys.Items.Add("Close key (long press)")
		Me.lbKeys.Items.Add("Home key")
		Me.lbKeys.Items.Add("Home key (long press)")
		Me.lbKeys.Location = New System.Drawing.Point(6, 39)
		Me.lbKeys.Name = "lbKeys"
		Me.lbKeys.Size = New System.Drawing.Size(228, 173)
		Me.lbKeys.TabIndex = 1
		'
		'lblChooseKeyFromList
		'
		Me.lblChooseKeyFromList.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lblChooseKeyFromList.BackColor = System.Drawing.Color.Lavender
		Me.lblChooseKeyFromList.Font = New System.Drawing.Font("Tahoma", 12.0!, System.Drawing.FontStyle.Regular)
		Me.lblChooseKeyFromList.Location = New System.Drawing.Point(7, 4)
		Me.lblChooseKeyFromList.Name = "lblChooseKeyFromList"
		Me.lblChooseKeyFromList.Size = New System.Drawing.Size(234, 23)
		Me.lblChooseKeyFromList.Text = "Choose key from list:"
		'
		'PictureBox2
		'
		Me.PictureBox2.BackColor = System.Drawing.Color.Lavender
		Me.PictureBox2.Dock = System.Windows.Forms.DockStyle.Top
		Me.PictureBox2.Location = New System.Drawing.Point(0, 0)
		Me.PictureBox2.Name = "PictureBox2"
		Me.PictureBox2.Size = New System.Drawing.Size(240, 33)
		'
		'KeyConfigTab
		'
		Me.KeyConfigTab.AutoScroll = True
		Me.KeyConfigTab.Controls.Add(Me.chkVibraEnabled)
		Me.KeyConfigTab.Controls.Add(Me.lblTime)
		Me.KeyConfigTab.Controls.Add(Me.btnBrowse)
		Me.KeyConfigTab.Controls.Add(Me.lblArguments)
		Me.KeyConfigTab.Controls.Add(Me.lblFile)
		Me.KeyConfigTab.Controls.Add(Me.txtArgs)
		Me.KeyConfigTab.Controls.Add(Me.txtPath)
		Me.KeyConfigTab.Controls.Add(Me.btnGoToKeysList)
		Me.KeyConfigTab.Controls.Add(Me.lblConfigureKeyHeader)
		Me.KeyConfigTab.Controls.Add(Me.intVibraTime)
		Me.KeyConfigTab.Controls.Add(Me.rbtnMinimize)
		Me.KeyConfigTab.Controls.Add(Me.rbtnClose)
		Me.KeyConfigTab.Controls.Add(Me.rbtnExecute)
		Me.KeyConfigTab.Controls.Add(Me.rbtnStandard)
		Me.KeyConfigTab.Controls.Add(Me.PictureBox1)
		Me.KeyConfigTab.Controls.Add(Me.rbtnStartMenu)
		Me.KeyConfigTab.Location = New System.Drawing.Point(0, 0)
		Me.KeyConfigTab.Name = "KeyConfigTab"
		Me.KeyConfigTab.Size = New System.Drawing.Size(232, 239)
		Me.KeyConfigTab.Text = "Configure Key"
		'
		'chkVibraEnabled
		'
		Me.chkVibraEnabled.Location = New System.Drawing.Point(6, 35)
		Me.chkVibraEnabled.Name = "chkVibraEnabled"
		Me.chkVibraEnabled.Size = New System.Drawing.Size(97, 20)
		Me.chkVibraEnabled.TabIndex = 14
		Me.chkVibraEnabled.Text = "Vibrate"
		'
		'lblTime
		'
		Me.lblTime.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lblTime.Font = New System.Drawing.Font("Tahoma", 8.0!, System.Drawing.FontStyle.Regular)
		Me.lblTime.Location = New System.Drawing.Point(100, 36)
		Me.lblTime.Name = "lblTime"
		Me.lblTime.Size = New System.Drawing.Size(79, 20)
		Me.lblTime.Text = "Time:"
		Me.lblTime.TextAlign = System.Drawing.ContentAlignment.TopRight
		'
		'btnBrowse
		'
		Me.btnBrowse.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.btnBrowse.BackColor = System.Drawing.Color.Gainsboro
		Me.btnBrowse.Location = New System.Drawing.Point(191, 126)
		Me.btnBrowse.Name = "btnBrowse"
		Me.btnBrowse.Size = New System.Drawing.Size(33, 21)
		Me.btnBrowse.TabIndex = 23
		Me.btnBrowse.Text = "..."
		'
		'lblArguments
		'
		Me.lblArguments.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lblArguments.Location = New System.Drawing.Point(6, 147)
		Me.lblArguments.Name = "lblArguments"
		Me.lblArguments.Size = New System.Drawing.Size(167, 16)
		Me.lblArguments.Text = "Arguments:"
		'
		'lblFile
		'
		Me.lblFile.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lblFile.Location = New System.Drawing.Point(6, 110)
		Me.lblFile.Name = "lblFile"
		Me.lblFile.Size = New System.Drawing.Size(158, 16)
		Me.lblFile.Text = "File:"
		'
		'txtArgs
		'
		Me.txtArgs.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.txtArgs.Enabled = False
		Me.txtArgs.Location = New System.Drawing.Point(6, 163)
		Me.txtArgs.Name = "txtArgs"
		Me.txtArgs.Size = New System.Drawing.Size(218, 21)
		Me.txtArgs.TabIndex = 19
		'
		'txtPath
		'
		Me.txtPath.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.txtPath.Enabled = False
		Me.txtPath.Location = New System.Drawing.Point(6, 126)
		Me.txtPath.Name = "txtPath"
		Me.txtPath.Size = New System.Drawing.Size(179, 21)
		Me.txtPath.TabIndex = 18
		'
		'btnGoToKeysList
		'
		Me.btnGoToKeysList.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.btnGoToKeysList.BackColor = System.Drawing.Color.Gainsboro
		Me.btnGoToKeysList.Location = New System.Drawing.Point(164, 3)
		Me.btnGoToKeysList.Name = "btnGoToKeysList"
		Me.btnGoToKeysList.Size = New System.Drawing.Size(60, 24)
		Me.btnGoToKeysList.TabIndex = 16
		Me.btnGoToKeysList.Text = "<<"
		'
		'lblConfigureKeyHeader
		'
		Me.lblConfigureKeyHeader.BackColor = System.Drawing.Color.Lavender
		Me.lblConfigureKeyHeader.Location = New System.Drawing.Point(6, 4)
		Me.lblConfigureKeyHeader.Name = "lblConfigureKeyHeader"
		Me.lblConfigureKeyHeader.Size = New System.Drawing.Size(228, 25)
		'
		'intVibraTime
		'
		Me.intVibraTime.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.intVibraTime.Enabled = False
		Me.intVibraTime.Location = New System.Drawing.Point(184, 35)
		Me.intVibraTime.MaxLength = 5
		Me.intVibraTime.Name = "intVibraTime"
		Me.intVibraTime.Size = New System.Drawing.Size(41, 21)
		Me.intVibraTime.TabIndex = 15
		Me.intVibraTime.Text = "1000"
		'
		'rbtnMinimize
		'
		Me.rbtnMinimize.Location = New System.Drawing.Point(7, 206)
		Me.rbtnMinimize.Name = "rbtnMinimize"
		Me.rbtnMinimize.Size = New System.Drawing.Size(112, 22)
		Me.rbtnMinimize.TabIndex = 13
		Me.rbtnMinimize.Text = "Minimize"
		'
		'rbtnClose
		'
		Me.rbtnClose.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.rbtnClose.Location = New System.Drawing.Point(113, 184)
		Me.rbtnClose.Name = "rbtnClose"
		Me.rbtnClose.Size = New System.Drawing.Size(111, 22)
		Me.rbtnClose.TabIndex = 12
		Me.rbtnClose.Text = "Close"
		'
		'rbtnExecute
		'
		Me.rbtnExecute.Location = New System.Drawing.Point(6, 85)
		Me.rbtnExecute.Name = "rbtnExecute"
		Me.rbtnExecute.Size = New System.Drawing.Size(212, 25)
		Me.rbtnExecute.TabIndex = 11
		Me.rbtnExecute.Text = "Execute"
		'
		'rbtnStandard
		'
		Me.rbtnStandard.Checked = True
		Me.rbtnStandard.Location = New System.Drawing.Point(6, 60)
		Me.rbtnStandard.Name = "rbtnStandard"
		Me.rbtnStandard.Size = New System.Drawing.Size(214, 25)
		Me.rbtnStandard.TabIndex = 10
		Me.rbtnStandard.Text = "Standard action"
		'
		'PictureBox1
		'
		Me.PictureBox1.BackColor = System.Drawing.Color.Lavender
		Me.PictureBox1.Dock = System.Windows.Forms.DockStyle.Top
		Me.PictureBox1.Location = New System.Drawing.Point(0, 0)
		Me.PictureBox1.Name = "PictureBox1"
		Me.PictureBox1.Size = New System.Drawing.Size(234, 33)
		'
		'rbtnStartMenu
		'
		Me.rbtnStartMenu.Location = New System.Drawing.Point(6, 184)
		Me.rbtnStartMenu.Name = "rbtnStartMenu"
		Me.rbtnStartMenu.Size = New System.Drawing.Size(112, 22)
		Me.rbtnStartMenu.TabIndex = 28
		Me.rbtnStartMenu.Text = "Start Menu"
		'
		'GlobalTab
		'
		Me.GlobalTab.Controls.Add(Me.chkEnableService)
		Me.GlobalTab.Controls.Add(Me.chkHookTaskBar)
		Me.GlobalTab.Controls.Add(Me.chkEnhanceToolbarWindows)
		Me.GlobalTab.Controls.Add(Me.lblGlobalSettings)
		Me.GlobalTab.Controls.Add(Me.PictureBox3)
		Me.GlobalTab.Controls.Add(Me.chkHomeIcon)
		Me.GlobalTab.Controls.Add(Me.chkLongPressAnimation)
		Me.GlobalTab.Location = New System.Drawing.Point(0, 0)
		Me.GlobalTab.Name = "GlobalTab"
		Me.GlobalTab.Size = New System.Drawing.Size(232, 239)
		Me.GlobalTab.Text = "Global"
		'
		'chkEnableService
		'
		Me.chkEnableService.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.chkEnableService.Checked = True
		Me.chkEnableService.CheckState = System.Windows.Forms.CheckState.Checked
		Me.chkEnableService.Location = New System.Drawing.Point(2, 198)
		Me.chkEnableService.Name = "chkEnableService"
		Me.chkEnableService.Size = New System.Drawing.Size(228, 40)
		Me.chkEnableService.TabIndex = 8
		Me.chkEnableService.Text = "Enable uTask service"
		'
		'chkHookTaskBar
		'
		Me.chkHookTaskBar.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.chkHookTaskBar.Checked = True
		Me.chkHookTaskBar.CheckState = System.Windows.Forms.CheckState.Checked
		Me.chkHookTaskBar.Location = New System.Drawing.Point(2, 158)
		Me.chkHookTaskBar.Name = "chkHookTaskBar"
		Me.chkHookTaskBar.Size = New System.Drawing.Size(228, 40)
		Me.chkHookTaskBar.TabIndex = 5
		Me.chkHookTaskBar.Text = "Hook task bar"
		'
		'chkEnhanceToolbarWindows
		'
		Me.chkEnhanceToolbarWindows.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.chkEnhanceToolbarWindows.Checked = True
		Me.chkEnhanceToolbarWindows.CheckState = System.Windows.Forms.CheckState.Checked
		Me.chkEnhanceToolbarWindows.Location = New System.Drawing.Point(2, 118)
		Me.chkEnhanceToolbarWindows.Name = "chkEnhanceToolbarWindows"
		Me.chkEnhanceToolbarWindows.Size = New System.Drawing.Size(228, 40)
		Me.chkEnhanceToolbarWindows.TabIndex = 2
		Me.chkEnhanceToolbarWindows.Text = "Enhance toolbar windows"
		'
		'lblGlobalSettings
		'
		Me.lblGlobalSettings.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lblGlobalSettings.BackColor = System.Drawing.Color.Lavender
		Me.lblGlobalSettings.Font = New System.Drawing.Font("Tahoma", 12.0!, System.Drawing.FontStyle.Regular)
		Me.lblGlobalSettings.Location = New System.Drawing.Point(6, 4)
		Me.lblGlobalSettings.Name = "lblGlobalSettings"
		Me.lblGlobalSettings.Size = New System.Drawing.Size(220, 25)
		Me.lblGlobalSettings.Text = "Global settings"
		'
		'PictureBox3
		'
		Me.PictureBox3.BackColor = System.Drawing.Color.Lavender
		Me.PictureBox3.Dock = System.Windows.Forms.DockStyle.Top
		Me.PictureBox3.Location = New System.Drawing.Point(0, 0)
		Me.PictureBox3.Name = "PictureBox3"
		Me.PictureBox3.Size = New System.Drawing.Size(232, 33)
		'
		'chkHomeIcon
		'
		Me.chkHomeIcon.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.chkHomeIcon.Checked = True
		Me.chkHomeIcon.CheckState = System.Windows.Forms.CheckState.Checked
		Me.chkHomeIcon.Location = New System.Drawing.Point(2, 78)
		Me.chkHomeIcon.Name = "chkHomeIcon"
		Me.chkHomeIcon.Size = New System.Drawing.Size(228, 40)
		Me.chkHomeIcon.TabIndex = 1
		Me.chkHomeIcon.Text = "Show home icon"
		'
		'chkLongPressAnimation
		'
		Me.chkLongPressAnimation.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.chkLongPressAnimation.Checked = True
		Me.chkLongPressAnimation.CheckState = System.Windows.Forms.CheckState.Checked
		Me.chkLongPressAnimation.Location = New System.Drawing.Point(2, 38)
		Me.chkLongPressAnimation.Name = "chkLongPressAnimation"
		Me.chkLongPressAnimation.Size = New System.Drawing.Size(228, 40)
		Me.chkLongPressAnimation.TabIndex = 0
		Me.chkLongPressAnimation.Text = "Long press animation"
		'
		'TodayWindowsTab
		'
		Me.TodayWindowsTab.Controls.Add(Me.btnClasses)
		Me.TodayWindowsTab.Controls.Add(Me.txtTodayWindows)
		Me.TodayWindowsTab.Controls.Add(Me.lblTodayClasses)
		Me.TodayWindowsTab.Location = New System.Drawing.Point(0, 0)
		Me.TodayWindowsTab.Name = "TodayWindowsTab"
		Me.TodayWindowsTab.Size = New System.Drawing.Size(232, 239)
		Me.TodayWindowsTab.Text = "Today"
		'
		'btnClasses
		'
		Me.btnClasses.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.btnClasses.Location = New System.Drawing.Point(146, 215)
		Me.btnClasses.Name = "btnClasses"
		Me.btnClasses.Size = New System.Drawing.Size(80, 20)
		Me.btnClasses.TabIndex = 3
		Me.btnClasses.Text = "Classes"
		'
		'txtTodayWindows
		'
		Me.txtTodayWindows.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
					Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.txtTodayWindows.Location = New System.Drawing.Point(6, 42)
		Me.txtTodayWindows.Multiline = True
		Me.txtTodayWindows.Name = "txtTodayWindows"
		Me.txtTodayWindows.Size = New System.Drawing.Size(220, 169)
		Me.txtTodayWindows.TabIndex = 1
		'
		'lblTodayClasses
		'
		Me.lblTodayClasses.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lblTodayClasses.Location = New System.Drawing.Point(6, 4)
		Me.lblTodayClasses.Name = "lblTodayClasses"
		Me.lblTodayClasses.Size = New System.Drawing.Size(220, 35)
		Me.lblTodayClasses.Text = "Following window classes will be treated as Today Windows:"
		'
		'ExceptionsTab
		'
		Me.ExceptionsTab.Controls.Add(Me.txtExceptions)
		Me.ExceptionsTab.Controls.Add(Me.lblExceptions)
		Me.ExceptionsTab.Location = New System.Drawing.Point(0, 0)
		Me.ExceptionsTab.Name = "ExceptionsTab"
		Me.ExceptionsTab.Size = New System.Drawing.Size(240, 241)
		Me.ExceptionsTab.Text = "Exceptions"
		'
		'txtExceptions
		'
		Me.txtExceptions.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
					Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.txtExceptions.Location = New System.Drawing.Point(6, 42)
		Me.txtExceptions.Multiline = True
		Me.txtExceptions.Name = "txtExceptions"
		Me.txtExceptions.Size = New System.Drawing.Size(228, 196)
		Me.txtExceptions.TabIndex = 3
		'
		'lblExceptions
		'
		Me.lblExceptions.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lblExceptions.Location = New System.Drawing.Point(6, 4)
		Me.lblExceptions.Name = "lblExceptions"
		Me.lblExceptions.Size = New System.Drawing.Size(228, 28)
		Me.lblExceptions.Text = "Following executable files will not be closed by uTask:"
		'
		'PositionFixTab
		'
		Me.PositionFixTab.Controls.Add(Me.btnClasses2)
		Me.PositionFixTab.Controls.Add(Me.chkPositionFixAuto)
		Me.PositionFixTab.Controls.Add(Me.chkPositionFixEnable)
		Me.PositionFixTab.Controls.Add(Me.lblPositionFixWarn)
		Me.PositionFixTab.Controls.Add(Me.txtPosFixNoFix)
		Me.PositionFixTab.Controls.Add(Me.txtPosFixToFix)
		Me.PositionFixTab.Location = New System.Drawing.Point(0, 0)
		Me.PositionFixTab.Name = "PositionFixTab"
		Me.PositionFixTab.Size = New System.Drawing.Size(232, 239)
		Me.PositionFixTab.Text = "PositionFix"
		'
		'btnClasses2
		'
		Me.btnClasses2.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.btnClasses2.Enabled = False
		Me.btnClasses2.Location = New System.Drawing.Point(146, 215)
		Me.btnClasses2.Name = "btnClasses2"
		Me.btnClasses2.Size = New System.Drawing.Size(80, 20)
		Me.btnClasses2.TabIndex = 6
		Me.btnClasses2.Text = "Classes"
		'
		'chkPositionFixAuto
		'
		Me.chkPositionFixAuto.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.chkPositionFixAuto.Enabled = False
		Me.chkPositionFixAuto.Location = New System.Drawing.Point(6, 30)
		Me.chkPositionFixAuto.Name = "chkPositionFixAuto"
		Me.chkPositionFixAuto.Size = New System.Drawing.Size(220, 30)
		Me.chkPositionFixAuto.TabIndex = 1
		Me.chkPositionFixAuto.Text = "Auto mode"
		'
		'chkPositionFixEnable
		'
		Me.chkPositionFixEnable.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.chkPositionFixEnable.Location = New System.Drawing.Point(6, 2)
		Me.chkPositionFixEnable.Name = "chkPositionFixEnable"
		Me.chkPositionFixEnable.Size = New System.Drawing.Size(220, 30)
		Me.chkPositionFixEnable.TabIndex = 0
		Me.chkPositionFixEnable.Text = "Enable position fix"
		'
		'lblPositionFixWarn
		'
		Me.lblPositionFixWarn.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lblPositionFixWarn.Enabled = False
		Me.lblPositionFixWarn.Location = New System.Drawing.Point(6, 60)
		Me.lblPositionFixWarn.Name = "lblPositionFixWarn"
		Me.lblPositionFixWarn.Size = New System.Drawing.Size(220, 35)
		Me.lblPositionFixWarn.Text = "Auto mode: these window classes WON'T be fixed"
		'
		'txtPosFixNoFix
		'
		Me.txtPosFixNoFix.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
					Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.txtPosFixNoFix.BackColor = System.Drawing.Color.PeachPuff
		Me.txtPosFixNoFix.Enabled = False
		Me.txtPosFixNoFix.Location = New System.Drawing.Point(6, 100)
		Me.txtPosFixNoFix.Multiline = True
		Me.txtPosFixNoFix.Name = "txtPosFixNoFix"
		Me.txtPosFixNoFix.Size = New System.Drawing.Size(220, 110)
		Me.txtPosFixNoFix.TabIndex = 4
		'
		'txtPosFixToFix
		'
		Me.txtPosFixToFix.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
					Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.txtPosFixToFix.BackColor = System.Drawing.Color.FromArgb(CType(CType(200, Byte), Integer), CType(CType(220, Byte), Integer), CType(CType(180, Byte), Integer))
		Me.txtPosFixToFix.Enabled = False
		Me.txtPosFixToFix.Location = New System.Drawing.Point(6, 100)
		Me.txtPosFixToFix.Multiline = True
		Me.txtPosFixToFix.Name = "txtPosFixToFix"
		Me.txtPosFixToFix.Size = New System.Drawing.Size(220, 110)
		Me.txtPosFixToFix.TabIndex = 2
		'
		'mainform
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(96.0!, 96.0!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi
		Me.ClientSize = New System.Drawing.Size(240, 268)
		Me.Controls.Add(Me.TabControl1)
		Me.KeyPreview = True
		Me.Menu = Me.mainMenu1
		Me.MinimizeBox = False
		Me.Name = "mainform"
		Me.Text = "uTask settings"
		Me.TabControl1.ResumeLayout(False)
		Me.KeysTab.ResumeLayout(False)
		Me.KeyConfigTab.ResumeLayout(False)
		Me.GlobalTab.ResumeLayout(False)
		Me.TodayWindowsTab.ResumeLayout(False)
		Me.ExceptionsTab.ResumeLayout(False)
		Me.PositionFixTab.ResumeLayout(False)
		Me.ResumeLayout(False)

	End Sub
	Friend WithEvents TabControl1 As System.Windows.Forms.TabControl
	Friend WithEvents KeysTab As System.Windows.Forms.TabPage
	Friend WithEvents lbKeys As System.Windows.Forms.ListBox
	Friend WithEvents lblChooseKeyFromList As System.Windows.Forms.Label
	Friend WithEvents GlobalTab As System.Windows.Forms.TabPage
	Friend WithEvents KeyConfigTab As System.Windows.Forms.TabPage
	Friend WithEvents lblConfigureKeyHeader As System.Windows.Forms.Label
	Friend WithEvents intVibraTime As System.Windows.Forms.TextBox
	Friend WithEvents chkVibraEnabled As System.Windows.Forms.CheckBox
	Friend WithEvents rbtnMinimize As System.Windows.Forms.RadioButton
	Friend WithEvents rbtnClose As System.Windows.Forms.RadioButton
	Friend WithEvents rbtnExecute As System.Windows.Forms.RadioButton
	Friend WithEvents rbtnStandard As System.Windows.Forms.RadioButton
	Friend WithEvents btnGoToConfigure As System.Windows.Forms.Button
	Friend WithEvents btnGoToKeysList As System.Windows.Forms.Button
	Friend WithEvents txtArgs As System.Windows.Forms.TextBox
	Friend WithEvents txtPath As System.Windows.Forms.TextBox
	Friend WithEvents lblArguments As System.Windows.Forms.Label
	Friend WithEvents lblFile As System.Windows.Forms.Label
	Friend WithEvents btnBrowse As System.Windows.Forms.Button
	Friend WithEvents lblTime As System.Windows.Forms.Label
	Friend WithEvents PictureBox2 As System.Windows.Forms.PictureBox
	Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
	Friend WithEvents menuCancel As System.Windows.Forms.MenuItem
	Friend WithEvents menuSave As System.Windows.Forms.MenuItem
	Friend WithEvents chkLongPressAnimation As System.Windows.Forms.CheckBox
	Friend WithEvents chkHomeIcon As System.Windows.Forms.CheckBox
	Friend WithEvents lblGlobalSettings As System.Windows.Forms.Label
	Friend WithEvents PictureBox3 As System.Windows.Forms.PictureBox
	Friend WithEvents TodayWindowsTab As System.Windows.Forms.TabPage
	Friend WithEvents txtTodayWindows As System.Windows.Forms.TextBox
	Friend WithEvents lblTodayClasses As System.Windows.Forms.Label
	Friend WithEvents ExceptionsTab As System.Windows.Forms.TabPage
	Friend WithEvents txtExceptions As System.Windows.Forms.TextBox
	Friend WithEvents lblExceptions As System.Windows.Forms.Label
	Friend WithEvents PositionFixTab As System.Windows.Forms.TabPage
	Friend WithEvents lblPositionFixWarn As System.Windows.Forms.Label
	Friend WithEvents txtPosFixToFix As System.Windows.Forms.TextBox
	Friend WithEvents chkPositionFixAuto As System.Windows.Forms.CheckBox
	Friend WithEvents chkPositionFixEnable As System.Windows.Forms.CheckBox
	Friend WithEvents rbtnStartMenu As System.Windows.Forms.RadioButton
	Friend WithEvents chkEnhanceToolbarWindows As System.Windows.Forms.CheckBox
	Friend WithEvents txtPosFixNoFix As System.Windows.Forms.TextBox
	Friend WithEvents chkHookTaskBar As System.Windows.Forms.CheckBox
	Friend WithEvents chkEnableService As System.Windows.Forms.CheckBox
	Friend WithEvents btnClasses As System.Windows.Forms.Button
	Friend WithEvents btnClasses2 As System.Windows.Forms.Button

End Class
