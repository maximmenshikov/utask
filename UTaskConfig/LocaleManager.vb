Public Class LocaleManager

	Private Class LocaleString
		Public Id As String
		Public LocalizedString As String
	End Class

	Private Shared LocaleList As New ArrayList
	Public Shared Sub Initialize()
		LocaleList.Clear()
		Dim lang As Integer = Microsoft.Win32.Registry.GetValue("HKEY_CURRENT_USER\MUI", "CurLang", 1033)
		Dim hexlang As String = Hex(lang).ToString.PadLeft(4, "0")

		Dim filePath As String = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().GetName().CodeBase)
		Dim localepath As String = IO.Path.Combine(filePath, "utaskcfg." + hexlang.ToString + ".lng")
		If Not IO.File.Exists(localepath) Then
			localepath = IO.Path.Combine(filePath, "utaskcfg.0409.lng")
		End If
		localepath = localepath.Replace("file:\", "")


		If IO.File.Exists(localepath) Then
			Dim sr As IO.StreamReader = IO.File.OpenText(localepath)
			Dim s As String = sr.ReadLine()
			While Not s Is Nothing
				Dim locstr As New LocaleString
				If s.Contains("/") Then
					locstr.Id = s.Substring(0, s.IndexOf("/"))
					locstr.LocalizedString = s.Substring(s.IndexOf("/") + 1)
					LocaleList.Add(locstr)
				End If
				s = sr.ReadLine()
			End While
			sr.Close()
		End If
	End Sub

	Public Shared Sub Deinitialize()
		LocaleList.Clear()
	End Sub

	Public Shared Function GetString(ByVal Id As String) As String
		For x = 0 To LocaleList.Count - 1
			Dim locstr As LocaleString = LocaleList(x)
			If locstr.Id = id Then
				Return locstr.LocalizedString
			End If
		Next
		Return "< no translation >"
	End Function
End Class
