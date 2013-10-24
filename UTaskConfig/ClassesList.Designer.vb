<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Public Class ClassesList
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
		Me.menuBack = New System.Windows.Forms.MenuItem
		Me.lbClasses = New System.Windows.Forms.ListBox
		Me.menuAdd = New System.Windows.Forms.MenuItem
		Me.SuspendLayout()
		'
		'mainMenu1
		'
		Me.mainMenu1.MenuItems.Add(Me.menuBack)
		Me.mainMenu1.MenuItems.Add(Me.menuAdd)
		'
		'menuBack
		'
		Me.menuBack.Text = "Back"
		'
		'lbClasses
		'
		Me.lbClasses.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
					Or System.Windows.Forms.AnchorStyles.Left) _
					Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.lbClasses.Font = New System.Drawing.Font("Tahoma", 11.0!, System.Drawing.FontStyle.Regular)
		Me.lbClasses.Location = New System.Drawing.Point(3, 3)
		Me.lbClasses.Name = "lbClasses"
		Me.lbClasses.Size = New System.Drawing.Size(234, 254)
		Me.lbClasses.TabIndex = 0
		'
		'menuAdd
		'
		Me.menuAdd.Text = "Add"
		'
		'ClassesList
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(96.0!, 96.0!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi
		Me.AutoScroll = True
		Me.ClientSize = New System.Drawing.Size(240, 268)
		Me.Controls.Add(Me.lbClasses)
		Me.Menu = Me.mainMenu1
		Me.Name = "ClassesList"
		Me.Text = "Classes List"
		Me.ResumeLayout(False)

	End Sub
	Friend WithEvents menuBack As System.Windows.Forms.MenuItem
	Friend WithEvents lbClasses As System.Windows.Forms.ListBox
	Friend WithEvents menuAdd As System.Windows.Forms.MenuItem
End Class
