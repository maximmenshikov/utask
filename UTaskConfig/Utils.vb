Imports Microsoft.Win32
Public Class Utils

	Public Shared branch As String = "HKEY_CURRENT_USER\Software\ultrashot\UTask"
	Public Shared settingsBranch As String = "HKEY_CURRENT_USER\Software\ultrashot\UTask\Settings"
	Public Shared serviceBranch As String = "HKEY_LOCAL_MACHINE\Services\UTaskSrv"

	Public Shared Function Bool2Int(ByVal i1 As Boolean) As Integer
		If i1 = True Then
			Return 1
		End If
		Return 0
	End Function

	Public Shared Sub ReadFromRegistry(ByRef MyCommand As ExecCommand)
		Try
			Dim actionID As Integer = Registry.GetValue(settingsBranch, MyCommand.FullKeyName + "ActionID", -1)
			Dim fPath As String = ""
			Dim fArgs As String = ""

			fPath = Registry.GetValue(settingsBranch, MyCommand.FullKeyName + "Path", "")
			fArgs = Registry.GetValue(settingsBranch, MyCommand.FullKeyName + "Args", "")

			Dim isVibraEnabled As Integer = Registry.GetValue(settingsBranch, MyCommand.FullKeyName + "Vibra", 0)
			Dim VibraTime As Integer = Registry.GetValue(settingsBranch, MyCommand.FullKeyName + "VibraTime", 0)

			MyCommand.Action = actionID
			MyCommand.Command = fPath
			MyCommand.Arguments = fArgs
			MyCommand.VibraEnabled = isVibraEnabled
			MyCommand.VibraTime = VibraTime
		Catch ex As Exception
		End Try
	End Sub

	Public Shared Sub WriteToRegistry(ByVal MyCommand As ExecCommand)
		Try
			Registry.SetValue(settingsBranch, MyCommand.FullKeyName + "ActionID", MyCommand.Action, RegistryValueKind.DWord)
			Registry.SetValue(settingsBranch, MyCommand.FullKeyName + "Path", MyCommand.Command)
			Registry.SetValue(settingsBranch, MyCommand.FullKeyName + "Args", MyCommand.Arguments)
			Registry.SetValue(settingsBranch, MyCommand.FullKeyName + "Vibra", MyCommand.VibraEnabled)
			Registry.SetValue(settingsBranch, MyCommand.FullKeyName + "VibraTime", MyCommand.VibraTime)
		Catch ex As Exception
		End Try
	End Sub

End Class
