Imports System.Runtime.InteropServices
Class NativeFunctions


	<DllImport("coredll.dll")> Shared Function ServiceIoControl(ByVal hService As Integer, _
   ByVal dwIoControlCode As UInteger, _
  ByRef lpInBuffer As Integer, _
  ByVal NInBufferSize As Int32, _
  ByVal lpOutBuffer As IntPtr, _
  ByVal NOutBufferSize As Int32, _
  ByRef lpBytesReturned As Int32, _
  ByVal lpOverlapped As Integer) As Boolean
	End Function

	<DllImport("coredll.dll")> Shared Function GetServiceHandle(ByVal szPrefix As String, ByVal szDllName As String, ByVal pdwDllBuf As Integer) As Integer
	End Function

	<DllImport("coredll.dll")> Shared Function OpenEvent(ByVal dsDesiredAccess As UInteger, ByVal bInheritHandle As Integer, ByVal lpName As String) As UInt32
	End Function

	<DllImport("coredll.dll")> Shared Function EventModify(ByVal hEvent As UInt32, ByVal mode As UInt32) As Integer
	End Function

	<DllImport("htcAfe.dll")> Shared Function htcMessageBox(ByVal hWnd As UInteger, ByVal text As String, ByVal caption As String, ByVal type As Integer, ByVal unk As UInteger) As Windows.Forms.DialogResult
	End Function

End Class
