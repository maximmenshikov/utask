
Public Enum Action
    ACTION_NOACTION = 1
    ACTION_EXECUTE
    ACTION_CLOSE
	ACTION_MINIMIZE
	ACTION_STARTMENU
End Enum

Public Class ExecCommand

    Private _keyIndex As Integer
    Private _action As Action
    Private _command As String
    Private _args As String
    Private _fullkeyname As String
    Private _VibraEnabled As Integer
    Private _vibraTime As Integer
    Public Property KeyIndex() As Integer
        Get
            Return _keyIndex
        End Get
        Set(ByVal value As Integer)
            _keyIndex = value
        End Set
    End Property

    Public Property Action() As Action
        Get
            Return _action
        End Get
        Set(ByVal value As Action)
            _action = value
        End Set
    End Property

    Public Property Command() As String
        Get
            Return _command
        End Get
        Set(ByVal value As String)
            _command = value
        End Set
    End Property

    Public Property Arguments() As String
        Get
            Return _args
        End Get
        Set(ByVal value As String)
            _args = value
        End Set
    End Property

    Public Property FullKeyName() As String
        Get
            Return _fullkeyname
        End Get
        Set(ByVal value As String)
            _fullkeyname = value
        End Set
    End Property

    Public Property VibraEnabled() As Integer
        Get
            Return _VibraEnabled
        End Get
        Set(ByVal value As Integer)
            _VibraEnabled = value
        End Set
    End Property

    Public Property VibraTime() As Integer
        Get
            Return _vibraTime
        End Get
        Set(ByVal value As Integer)
            _vibraTime = value
        End Set
    End Property
End Class
