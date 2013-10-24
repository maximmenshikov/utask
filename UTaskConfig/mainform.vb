Imports Microsoft.Win32
Imports UTaskConfig.NativeFunctions
Imports System.Runtime.InteropServices

Public Class mainform

	Dim Commands(6) As ExecCommand

	Sub UpdateEditTab()
		If Not lbKeys.SelectedIndex = -1 Then
			Dim command As ExecCommand = Commands(lbKeys.SelectedIndex)
			chkVibraEnabled.Checked = CBool(command.VibraEnabled)
			intVibraTime.Text = command.VibraTime.ToString
			txtPath.Enabled = False
			txtArgs.Enabled = False
			btnBrowse.Enabled = False
			If command.Action = Action.ACTION_NOACTION Then
				rbtnStandard.Checked = True
			ElseIf command.Action = Action.ACTION_EXECUTE Then
				rbtnExecute.Checked = True
				txtPath.Enabled = True
				txtArgs.Enabled = True
				btnBrowse.Enabled = True
			ElseIf command.Action = Action.ACTION_CLOSE Then
				rbtnClose.Checked = True

			ElseIf command.Action = Action.ACTION_MINIMIZE Then
				rbtnMinimize.Checked = True
			Else
				rbtnStartMenu.Checked = True
			End If
			txtPath.Text = command.Command
			txtArgs.Text = command.Arguments

			If lbKeys.SelectedIndex > 3 Then
				rbtnClose.Visible = False
				rbtnMinimize.Visible = False
			Else
				rbtnClose.Visible = True
				rbtnMinimize.Visible = True
			End If
		End If
	End Sub

#Region "Buttons"

	Private Sub btnGoToConfigure_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnGoToConfigure.Click
		TabControl1.SelectedIndex = 1
	End Sub

	Private Sub btnGoToKeysList_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnGoToKeysList.Click
		TabControl1.SelectedIndex = 0
	End Sub

#End Region

#Region "Localization"

	Private Sub ApplyLocalization()
		Me.Text = LocaleManager.GetString("uTaskSettings")
		menuCancel.Text = LocaleManager.GetString("Cancel")
		menuSave.Text = LocaleManager.GetString("Save")

		KeysTab.Text = LocaleManager.GetString("Keys")
		lblChooseKeyFromList.Text = LocaleManager.GetString("ChooseKeyFromList") + ":"
		lbKeys.Items.Clear()
		lbKeys.Items.Add(LocaleManager.GetString("WindowsKey"))
		lbKeys.Items.Add(LocaleManager.GetString("WindowsKeyLong"))
		lbKeys.Items.Add(LocaleManager.GetString("CloseKey"))
		lbKeys.Items.Add(LocaleManager.GetString("CloseKeyLong"))
		lbKeys.Items.Add(LocaleManager.GetString("HomeKey"))
		lbKeys.Items.Add(LocaleManager.GetString("HomeKeyLong"))

		KeyConfigTab.Text = LocaleManager.GetString("ConfigureKey")
		chkVibraEnabled.Text = LocaleManager.GetString("Vibrate")
		lblTime.Text = LocaleManager.GetString("Time") + ":"
		rbtnStandard.Text = LocaleManager.GetString("StandardAction")
		rbtnExecute.Text = LocaleManager.GetString("Execute")
		lblFile.Text = LocaleManager.GetString("File") + ":"
		lblArguments.Text = LocaleManager.GetString("Arguments") + ":"
		rbtnClose.Text = LocaleManager.GetString("Close")
		rbtnMinimize.Text = LocaleManager.GetString("Minimize")
		rbtnStartMenu.Text = LocaleManager.GetString("StartMenu")

		GlobalTab.Text = LocaleManager.GetString("Global")
		lblGlobalSettings.Text = LocaleManager.GetString("GlobalSettings")
		chkLongPressAnimation.Text = LocaleManager.GetString("LongPressAnimation")
		chkHomeIcon.Text = LocaleManager.GetString("ShowHomeIcon")
		chkEnableService.Text = LocaleManager.GetString("EnableService")

		TodayWindowsTab.Text = LocaleManager.GetString("Today")
		lblTodayClasses.Text = LocaleManager.GetString("TodayMsg")

		ExceptionsTab.Text = LocaleManager.GetString("Exceptions")
		lblExceptions.Text = LocaleManager.GetString("ExceptionsMsg")

		PositionFixTab.Text = LocaleManager.GetString("PositionFix")
		chkPositionFixEnable.Text = LocaleManager.GetString("PositionFixEnable")
		chkPositionFixAuto.Text = LocaleManager.GetString("PositionFixAutoMode")
		chkEnhanceToolbarWindows.Text = LocaleManager.GetString("EnhanceToolbarWindows")
		chkHookTaskBar.Text = LocaleManager.GetString("HookTaskBar")

		btnClasses.Text = LocaleManager.GetString("Classes")
		btnClasses2.Text = LocaleManager.GetString("Classes")

	End Sub

#End Region

	Private Sub lbKeys_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles lbKeys.SelectedIndexChanged
		If lbKeys.SelectedIndex = -1 Then
			btnGoToConfigure.Visible = False
			lblConfigureKeyHeader.Text = ""
		Else
			btnGoToConfigure.Visible = True
			lblConfigureKeyHeader.Text = lbKeys.SelectedItem
		End If
		UpdateEditTab()
	End Sub

#Region "Form"

	Dim isSaving As Boolean = False

	Private Sub Form1_Closing(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles MyBase.Closing
		If isSaving = True Then
			'If MyMessageBox.ShowQuestion(LocaleManager.GetString("CloseWarn"), "uTask") = Windows.Forms.DialogResult.No Then 'MessageBox.Show(LocaleManager.GetString("CloseWarn"), "uTask", MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2) = Windows.Forms.DialogResult.No Then
			If MyMessageBox.Show(LocaleManager.GetString("CloseWarn"), "uTask", MessageBoxButtons.YesNo, MessageBoxIcon.Question) = DialogResult.No Then
				e.Cancel = True
			Else
				For x = 0 To 5
					Utils.WriteToRegistry(Commands(x))
				Next

				Registry.SetValue(Utils.settingsBranch, "ShowHoldAnimation", Utils.Bool2Int(chkLongPressAnimation.Checked), RegistryValueKind.DWord)
				Registry.SetValue(Utils.settingsBranch, "ShowHomeIcon", Utils.Bool2Int(chkHomeIcon.Checked), RegistryValueKind.DWord)
				Registry.SetValue(Utils.settingsBranch, "PositionFix", Utils.Bool2Int(chkPositionFixEnable.Checked), RegistryValueKind.DWord)
				Registry.SetValue(Utils.settingsBranch, "PositionFix_AutoMode", Utils.Bool2Int(chkPositionFixAuto.Checked), RegistryValueKind.DWord)
				Registry.SetValue(Utils.settingsBranch, "EnhanceToolbarWindows", Utils.Bool2Int(chkEnhanceToolbarWindows.Checked), RegistryValueKind.DWord)
				Registry.SetValue(Utils.settingsBranch, "HookTaskBar", Utils.Bool2Int(chkHookTaskBar.Checked), RegistryValueKind.DWord)
				Dim flag As Integer

				If chkEnableService.Checked = True Then
					flag = 0
				Else
					flag = 4
				End If

				Dim ShowResetWarn As Boolean = True
				If (flag = 0 And oldFlagValue = 1) Or (flag = 4 And oldFlagValue = 0) Then
					ShowResetWarn = False
				End If
				Registry.SetValue(Utils.serviceBranch, "Flags", flag, RegistryValueKind.DWord)

				WriteTodayWindows()
				WriteExclusiveList()
				WritePositionFix_ToFix_List()
				WritePositionFix_NoFix_List()

				Dim handle As Integer = GetServiceHandle("UTS0:", Nothing, 0)
				If Not handle = -1 And Not handle = 0 Then
					Dim controlcode As Integer = 2560
					ServiceIoControl(handle, 17039388, controlcode, 4, IntPtr.Zero, 0, 0, 0)
				End If

				Dim hEvent As UInt32 = OpenEvent(2031619, 0, "Global\UTask\HookUpdateEvent")
				If Not hEvent = 0 Then
					EventModify(hEvent, 3)
				End If

				If ShowResetWarn = True Then
					MyMessageBox.Show(LocaleManager.GetString("ResetWarn"), "uTask", MessageBoxButtons.OK, MessageBoxIcon.Question)
				End If
			End If
		End If
		isSaving = False
	End Sub

	Dim oldFlagValue As Integer = 0
	Private Sub Form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Load
		LocaleManager.Initialize()
		ApplyLocalization()

		For x = 0 To 5
			Commands(x) = New ExecCommand
		Next
		Commands(0).FullKeyName = "LKey"
		Commands(1).FullKeyName = "LKeyLong"
		Commands(2).FullKeyName = "RKey"
		Commands(3).FullKeyName = "RKeyLong"
		Commands(4).FullKeyName = "HomeKey"
		Commands(5).FullKeyName = "HomeKeyLong"
		For x = 0 To 5
			Utils.ReadFromRegistry(Commands(x))
		Next

		ReadTodayWindows()
		ReadExclusiveList()
		ReadPositionFix_ToFix_List()
		ReadPositionFix_NoFix_List()

		chkLongPressAnimation.Checked = CBool(Registry.GetValue(Utils.settingsBranch, "ShowHoldAnimation", 1))
		chkHomeIcon.Checked = CBool(Registry.GetValue(Utils.settingsBranch, "ShowHomeIcon", 1))

		chkPositionFixEnable.Checked = CBool(Registry.GetValue(Utils.settingsBranch, "PositionFix", 1))
		chkPositionFixAuto.Checked = CBool(Registry.GetValue(Utils.settingsBranch, "PositionFix_AutoMode", 1))

		chkEnhanceToolbarWindows.Checked = CBool(Registry.GetValue(Utils.settingsBranch, "EnhanceToolbarWindows", 1))
		chkHookTaskBar.Checked = CBool(Registry.GetValue(Utils.settingsBranch, "HookTaskBar", 0))

		Dim flags As Integer = Registry.GetValue(Utils.serviceBranch, "Flags", 0)
		If (flags And 4) = 4 Then
			chkEnableService.Checked = False
			oldFlagValue = 0
		Else
			chkEnableService.Checked = True
			oldFlagValue = 1
		End If
		chkPositionFixAuto_CheckStateChanged(0, e)
		lbKeys.SelectedIndex = 0
	End Sub

#End Region

#Region "Lists"

#Region "TodayWindows"

	Sub ReadTodayWindows()
		Try
			Dim regkey As RegistryKey = Registry.CurrentUser.OpenSubKey(Utils.branch.Replace("HKEY_CURRENT_USER\", "") + "\TodayWindows", False)
			Dim values() As String = regkey.GetValueNames()
			Array.Sort(values)
			Dim result As String = ""
			For Each value In values
				result = result + value + vbCrLf
			Next
			txtTodayWindows.Text = result
		Catch ex As Exception
		End Try
	End Sub

	Sub WriteTodayWindows()
		Try
			Dim regkey As RegistryKey = Registry.CurrentUser.CreateSubKey(Utils.branch.Replace("HKEY_CURRENT_USER\", "") + "\TodayWindows")
			Dim values() As String = regkey.GetValueNames
			For Each value In values
				regkey.DeleteValue(value)
			Next
			Dim s As String = txtTodayWindows.Text.Replace(vbCrLf, ";")

			Dim lines() As String = s.Split(";")
			For Each line In lines
				Dim templine As String = line.Replace(" ", "")
				If Not templine.Length = 0 Then
					regkey.SetValue(line, 0, RegistryValueKind.DWord)
				End If
			Next
		Catch ex As Exception
		End Try
	End Sub

#End Region

#Region "ExclusiveList"

	Sub ReadExclusiveList()
		Try
			Dim regkey As RegistryKey = Registry.CurrentUser.OpenSubKey(Utils.branch.Replace("HKEY_CURRENT_USER\", "") + "\ExclusiveList", False)
			Dim values() As String = regkey.GetValueNames()
			Array.Sort(values)
			Dim result As String = ""
			For Each value In values
				result = result + value + vbCrLf
			Next
			txtExceptions.Text = result
		Catch ex As Exception
		End Try
	End Sub

	Sub WriteExclusiveList()
		Try
			Dim regkey As RegistryKey = Registry.CurrentUser.CreateSubKey(Utils.branch.Replace("HKEY_CURRENT_USER\", "") + "\ExclusiveList")
			Dim values() As String = regkey.GetValueNames
			For Each value In values
				regkey.DeleteValue(value)
			Next
			Dim s As String = txtExceptions.Text.Replace(vbCrLf, ";")
			Dim lines() As String = s.Split(";")
			For Each line In lines
				Dim templine As String = line.Replace(" ", "")
				If Not templine.Length = 0 Then
					regkey.SetValue(line, 0, RegistryValueKind.DWord)
				End If
			Next
		Catch ex As Exception
		End Try
	End Sub

#End Region

#Region "PositionFix_ToFix"

	Sub ReadPositionFix_ToFix_List()
		Try
			Dim regkey As RegistryKey = Registry.CurrentUser.OpenSubKey(Utils.branch.Replace("HKEY_CURRENT_USER\", "") + "\PositionFix\Fix", False)
			Dim values() As String = regkey.GetValueNames()
			Array.Sort(values)
			Dim result As String = ""
			For Each value In values
				result = result + value + vbCrLf
			Next
			txtPosFixToFix.Text = result
		Catch ex As Exception
		End Try
	End Sub

	Sub WritePositionFix_ToFix_List()
		Try
			Dim regkey As RegistryKey = Registry.CurrentUser.CreateSubKey(Utils.branch.Replace("HKEY_CURRENT_USER\", "") + "\PositionFix\Fix")
			Dim values() As String = regkey.GetValueNames
			For Each value In values
				regkey.DeleteValue(value)
			Next
			Dim s As String = txtPosFixToFix.Text.Replace(vbCrLf, ";")
			Dim lines() As String = s.Split(";")
			For Each line In lines
				Dim templine As String = line.Replace(" ", "")
				If Not templine.Length = 0 Then
					regkey.SetValue(line, 0, RegistryValueKind.DWord)
				End If
			Next
		Catch ex As Exception
		End Try
	End Sub

#End Region

#Region "PositionFix_NoFix"

	Sub ReadPositionFix_NoFix_List()
		txtPosFixNoFix.Text = ""
		Try
			Dim regkey As RegistryKey = Registry.CurrentUser.OpenSubKey(Utils.branch.Replace("HKEY_CURRENT_USER\", "") + "\PositionFix\NoFix", False)
			Dim values() As String = regkey.GetValueNames()
			Array.Sort(values)
			Dim result As String = ""
			For Each value In values
				result = result + value + vbCrLf
			Next
			txtPosFixNoFix.Text = result
		Catch ex As Exception
		End Try
	End Sub

	Sub WritePositionFix_NoFix_List()
		Try
			Dim regkey As RegistryKey = Registry.CurrentUser.CreateSubKey(Utils.branch.Replace("HKEY_CURRENT_USER\", "") + "\PositionFix\NoFix")
			Dim values() As String = regkey.GetValueNames
			For Each value In values
				regkey.DeleteValue(value)
			Next
			Dim s As String = txtPosFixNoFix.Text.Replace(vbCrLf, ";")
			Dim lines() As String = s.Split(";")
			For Each line In lines
				Dim templine As String = line.Replace(" ", "")
				If Not templine.Length = 0 Then
					regkey.SetValue(line, 0, RegistryValueKind.DWord)
				End If
			Next
		Catch ex As Exception
		End Try
	End Sub

#End Region

#End Region

	Private Sub menuCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles menuCancel.Click
		Me.Close()
	End Sub

	Private Sub menuSave_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles menuSave.Click
		isSaving = True
		Me.Close()
	End Sub

#Region "Key's preferred options"

	Private Sub chkVibraEnabled_CheckStateChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chkVibraEnabled.CheckStateChanged

		If chkVibraEnabled.Checked = True Then
			intVibraTime.Enabled = True
			If Not lbKeys.SelectedIndex = -1 Then
				Commands(lbKeys.SelectedIndex).VibraEnabled = 1
			End If
		Else
			intVibraTime.Enabled = False
			If Not lbKeys.SelectedIndex = -1 Then
				Commands(lbKeys.SelectedIndex).VibraEnabled = 0
			End If
		End If

	End Sub


	Private Sub rbtnStandard_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles rbtnStandard.CheckedChanged
		If Not lbKeys.SelectedIndex = -1 Then
			If rbtnStandard.Checked = True Then
				Commands(lbKeys.SelectedIndex).Action = Action.ACTION_NOACTION
			End If
		End If
	End Sub

	Private Sub rbtnExecute_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles rbtnExecute.CheckedChanged
		If rbtnExecute.Checked = True Then
			txtPath.Enabled = True
			txtArgs.Enabled = True
			btnBrowse.Enabled = True
			If Not lbKeys.SelectedIndex = -1 Then
				Commands(lbKeys.SelectedIndex).Action = Action.ACTION_EXECUTE
			End If
		Else
			txtPath.Enabled = False
			txtArgs.Enabled = False
			btnBrowse.Enabled = False
		End If
	End Sub

	Private Sub rbtnClose_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles rbtnClose.CheckedChanged
		If Not lbKeys.SelectedIndex = -1 Then
			If rbtnClose.Checked = True Then
				Commands(lbKeys.SelectedIndex).Action = Action.ACTION_CLOSE
			End If
		End If
	End Sub

	Private Sub rbtnMinimize_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles rbtnMinimize.CheckedChanged
		If Not lbKeys.SelectedIndex = -1 Then
			If rbtnMinimize.Checked = True Then
				Commands(lbKeys.SelectedIndex).Action = Action.ACTION_MINIMIZE
			End If
		End If
	End Sub

	Private Sub rbtnStartMenu_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles rbtnStartMenu.CheckedChanged
		If Not lbKeys.SelectedIndex = -1 Then
			If rbtnStartMenu.Checked = True Then
				Commands(lbKeys.SelectedIndex).Action = Action.ACTION_STARTMENU
			End If
		End If
	End Sub

	Private Function isNum(ByVal text As String) As Boolean
		If Microsoft.VisualBasic.Information.IsNumeric(text) = True Then
			Return True
		End If
		Return False
	End Function
	Private Sub intVibraTime_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles intVibraTime.TextChanged
		Dim numeric As Boolean = isNum(intVibraTime.Text)
		If numeric = True Then
			If Not lbKeys.SelectedIndex = -1 Then
				Commands(lbKeys.SelectedIndex).VibraTime = Int(intVibraTime.Text)
			End If
			intVibraTime.BackColor = Drawing.Color.White
		Else
			intVibraTime.BackColor = Drawing.Color.Red
		End If
	End Sub

	Private Sub btnBrowse_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnBrowse.Click
		Dim ofd As New MobilePractices.OpenFileDialogEx.OpenFileDialogEx
		ofd.Filter = "*.exe;*.lnk"
		ofd.currentPath = "\"
		ofd.ROOT = "\"
		ofd.Text = "Select file"
		If ofd.ShowDialog() = Windows.Forms.DialogResult.OK Then
			txtPath.Text = ofd.FileName
		End If
	End Sub

	Private Sub txtPath_TextChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtPath.TextChanged
		If Not lbKeys.SelectedIndex = -1 Then
			Commands(lbKeys.SelectedIndex).Command = txtPath.Text
		End If
	End Sub

	Private Sub txtArgs_TextChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtArgs.TextChanged
		If Not lbKeys.SelectedIndex = -1 Then
			Commands(lbKeys.SelectedIndex).Arguments = txtArgs.Text
		End If
	End Sub

#End Region

	Private Sub chkPositionFixAuto_CheckStateChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chkPositionFixAuto.CheckStateChanged
		If chkPositionFixAuto.Checked = True Then
			lblPositionFixWarn.Text = LocaleManager.GetString("PositionFixWarnInAuto")
			txtPosFixNoFix.Visible = True
			txtPosFixToFix.Visible = False
		Else
			lblPositionFixWarn.Text = LocaleManager.GetString("PositionFixWarn")
			txtPosFixNoFix.Visible = False
			txtPosFixToFix.Visible = True
		End If
	End Sub

	Private Sub chkPositionFixEnable_CheckStateChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chkPositionFixEnable.CheckStateChanged
		'If chkPositionFixEnable.Enabled = True Then
		chkPositionFixAuto.Enabled = chkPositionFixEnable.Checked
		txtPosFixToFix.Enabled = chkPositionFixEnable.Checked
		txtPosFixNoFix.Enabled = chkPositionFixEnable.Checked
		lblPositionFixWarn.Enabled = chkPositionFixEnable.Checked
		btnClasses2.Enabled = chkPositionFixEnable.Checked
		'End If
	End Sub


	Private Sub KeyConfigTab_GotFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles KeyConfigTab.GotFocus
		'btnGoToKeysList.Location = New System.Drawing.Point(KeyConfigTab.ClientSize.Width - 7 - btnGoToKeysList.Size.Width, 3)
		'btnGoToKeysList.Location = New System.Drawing.Point(KeyConfigTab.Width - 7 - btnGoToKeysList.Size.Width, 3)
	End Sub

	'Private Sub KeyConfigTab_Resize(ByVal sender As Object, ByVal e As System.EventArgs) Handles KeyConfigTab.Resize
	'	btnGoToKeysList.Location = New System.Drawing.Point(KeyConfigTab.ClientSize.Width - 7 - btnGoToKeysList.Size.Width, 3)
	'End Sub

	Private Sub KeysTab_GotFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles KeysTab.GotFocus
		'btnGoToConfigure.Location = New System.Drawing.Point(KeyConfigTab.ClientSize.Width - 7 - btnGoToConfigure.Size.Width, 3)
		'btnGoToConfigure.Location = New System.Drawing.Point(KeyConfigTab.Width - 7 - btnGoToConfigure.Size.Width, 3)
	End Sub

	'Private Sub KeysTab_Resize(ByVal sender As Object, ByVal e As System.EventArgs) Handles KeysTab.Resize
	'	btnGoToConfigure.Location = New System.Drawing.Point(KeyConfigTab.ClientSize.Width - 7 - btnGoToConfigure.Size.Width, 3)
	'End Sub

	Private Sub mainform_Resize(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Resize
		If Me.Width > Me.Height Then
			GlobalTab.AutoScroll = True
			KeyConfigTab.AutoScroll = True
		Else
			GlobalTab.AutoScroll = False
			KeyConfigTab.AutoScroll = False
		End If
	End Sub

	Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClasses.Click
		ClassesList.mode = 0
		ClassesList.ShowDialog()
	End Sub

	Private Sub btnClasses2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClasses2.Click
		ClassesList.mode = 1 + Utils.Bool2Int(chkPositionFixAuto.Checked)
		ClassesList.ShowDialog()
	End Sub

End Class
