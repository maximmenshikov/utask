Public Class MyMessageBox

	Public Shared Function Show(ByVal text As String, _
	 Optional ByVal caption As String = "", _
	 Optional ByVal buttons As MessageBoxButtons = MessageBoxButtons.OK, _
	 Optional ByVal icon As MessageBoxIcon = MessageBoxIcon.None, _
	 Optional ByVal defbtn As MessageBoxDefaultButton = MessageBoxDefaultButton.Button1) As Windows.Forms.DialogResult
		If IO.File.Exists("\Windows\htcAfe.dll") = False Then
			GoTo msbox
		Else
			Try
				Dim condition As UInt32 = defbtn + icon + buttons
				Return NativeFunctions.htcMessageBox(mainform.Handle, text, caption, condition, 0)
			Catch ex As Exception
				GoTo msbox
			End Try

		End If
msbox:
		Return MessageBox.Show(text, caption, MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2)
	End Function

End Class
