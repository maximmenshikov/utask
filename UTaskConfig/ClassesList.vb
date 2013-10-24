Imports System.Text

Public Class ClassesList

	Declare Function GetWindow Lib "coredll.dll" (ByVal hWnd As IntPtr, ByVal uCmd As UInt32) As IntPtr
	Declare Function GetClassName Lib "coredll.dll" (ByVal hWnd As IntPtr, ByVal buf As StringBuilder, ByVal nMaxCount As Integer) As Integer

	Public mode As Integer = 0

	Private Sub ApplyLocalization()
		Me.Text = LocaleManager.GetString("ClassesList")
		menuBack.Text = LocaleManager.GetString("Back")
		menuAdd.Text = LocaleManager.GetString("Add")
	End Sub
	Private Sub ClassesList_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
		ApplyLocalization()
		lbClasses.Items.Clear()
		Dim arr As New ArrayList
		Dim h As IntPtr = GetWindow(Me.Handle, 0)
		While True
			h = GetWindow(h, 2)
			If h = 0 Then
				Exit While
			End If
			Dim sb As New StringBuilder(256)
			GetClassName(h, sb, sb.Capacity)
			arr.Add(sb.ToString)
			'ListBox1.Items.Add(sb.ToString)
		End While
		arr.Sort()

		Dim previousString As String = ""
		For x = 0 To arr.Count - 1
			Dim s As String = arr(x)
			If Not s = previousString Then
				lbClasses.Items.Add(s)
			End If
			previousString = s
		Next
	End Sub

	Private Sub MenuItem1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles menuBack.Click
		Me.Close()
	End Sub

	Private Sub MenuItem2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles menuAdd.Click
		If Not lbClasses.SelectedIndex = -1 Then
			Dim txtbox As TextBox
			If mode = 0 Then
				txtbox = mainform.txtTodayWindows
			ElseIf mode = 1 Then
				txtbox = mainform.txtPosFixToFix
			Else
				txtbox = mainform.txtPosFixNoFix
			End If
			If txtbox.Text.Length > 2 Then
				If Not txtbox.Text.Substring(txtbox.Text.Length - 2, 2) = vbCrLf Then
					txtbox.Text = txtbox.Text + vbCrLf
				End If
			End If
			txtbox.Text = txtbox.Text + lbClasses.SelectedItem
		End If
		Me.Close()
	End Sub
End Class