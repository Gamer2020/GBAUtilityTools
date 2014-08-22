Imports VB = Microsoft.VisualBasic
Imports System.IO

Module MainMod

    Public LoadedRom As String
    Public i As Integer
    Public FileNum As Integer
    Public AppPath As String = System.AppDomain.CurrentDomain.BaseDirectory() & IIf(Right(System.AppDomain.CurrentDomain.BaseDirectory(), 1) = "\", "", "\")
    Public biosbuffer As String

    Sub Main()
        Dim strStartupArguments() As String, intCount As Integer
        strStartupArguments = System.Environment.GetCommandLineArgs

        If UBound(strStartupArguments) < 1 Then
            showhelp()
        End If

        For intCount = 0 To UBound(strStartupArguments)
            Select Case strStartupArguments(intCount).ToLower
                Case "help"
                    showhelp()
                Case Else
                    System.Console.WriteLine("GBA Bios Fixer")
                    System.Console.WriteLine("Copyright (c) 2013 Gamer2020 All rights reserved.")
                    System.Console.WriteLine("")
                    StartStuff()
            End Select
        Next intCount
    End Sub

    Sub showhelp()
        System.Console.WriteLine("GBA Bios Fixer")
        System.Console.WriteLine("Copyright (c) 2013 Gamer2020 All rights reserved.")
        System.Console.WriteLine("")
        System.Console.WriteLine("This program fixes a GBA bios that has been dumped as a SAV file.")
        System.Console.WriteLine("")
        System.Console.WriteLine("help")
        System.Console.WriteLine("Shows this help text.")
        System.Console.WriteLine("")
        System.Console.WriteLine("The only paramater you need is the location of your SAV.")
        System.Console.WriteLine("You can just drag the SAV onto the program if you wish.")
        System.Console.WriteLine("EX: GBABiosFixer.exe C:/GBAUtilityTools.sav")
        System.Console.ReadLine()
        End
    End Sub

    Sub StartStuff()
        LoadedRom = System.Environment.GetCommandLineArgs(1)
        
        If System.IO.File.Exists(LoadedRom) = False Then
            filenoreal()
        End If

        starttheprocess()

        End
    End Sub

    Sub filenoreal()
        System.Console.WriteLine("The file doesn't exist.")
        System.Console.WriteLine("")
        System.Console.WriteLine("Press any key to exit...")
        System.Console.ReadLine()
        End
    End Sub

    Sub starttheprocess()
        biosbuffer = ReadHEX(LoadedRom, 0, 16384)

        WriteHEX(AppPath & "gba_bios.bin", 0, biosbuffer)

        System.Console.WriteLine("")
        System.Console.WriteLine("Done! Press any key to exit...")
        System.Console.ReadLine()
        End
    End Sub

End Module
