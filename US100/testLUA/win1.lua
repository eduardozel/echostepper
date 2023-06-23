-- LuaForWindows_v5.1.5-52

 require("gpUS100")


 local wx = require("wx")

    frame = wx.wxFrame( wx.NULL, wx.wxID_ANY, "Test US-100"
                                 , wx.wxDefaultPosition, wx.wxSize( 350, 270)
                                 , wx.wxDEFAULT_FRAME_STYLE)

    frame:Show(true)
    frame:CreateStatusBar(1)
    notebook = wx.wxNotebook(frame, wx.wxID_ANY,
                                   wx.wxDefaultPosition, wx.wxDefaultSize)
                                   --wx.wxNB_BOTTOM)

    panelUS100()

wx.wxGetApp():MainLoop()
