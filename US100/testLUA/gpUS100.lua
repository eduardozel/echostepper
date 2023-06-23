 local wx = require("wx")
 require("COMPORT")

-- part 1


function panelUS100()
	panelGP = wx.wxPanel(notebook, wx.wxID_ANY)
	sizerBC = wx.wxBoxSizer(wx.wxVERTICAL)

	ID_BUTTON_Test		= 1010
	ID_TBOX_CONSOLE		= 1005


	cbFont = wx.wxFont(  12, wx.wxFONTFAMILY_MODERN, wx.wxFONTSTYLE_NORMAL, wx.wxFONTWEIGHT_NORMAL, false, "")

	btnSize = wx.wxSize( 60, 30)
	chSize	= wx.wxSize(  6, 10)

	tbCONSOLE = wx.wxTextCtrl( panelGP, ID_TBOX_CONSOLE, "+\n", wx.wxPoint(80, 20), wx.wxSize(240, 160), wx.wxTE_MULTILINE ) -- +wx.wxNO_BORDER
	tbFont = wx.wxFont(  12, wx.wxFONTFAMILY_MODERN, wx.wxFONTSTYLE_NORMAL, wx.wxFONTWEIGHT_NORMAL, false, "")
	tbCONSOLE:SetFont( tbFont )


-- -----------
    btnTest = wx.wxButton( panelGP, ID_BUTTON_Test, "get data",
                          wx.wxPoint( 00, 20), wx.wxSize( 80, 30) )
    frame:Connect( ID_BUTTON_Test, wx.wxEVT_COMMAND_BUTTON_CLICKED, OnGETCFG)


-- ---------
    notebook:AddPage(panelGP, "US-100")
end -- panelGpGSM


function strToHost( msg )
	for i = 1, string.len(msg) do
		sendCOM_HOST( string.sub( msg, i, i) )
	end -- for i
end -- strToHost

function getRply(
)
	local rd_len = 1
	local timeout = 4000
        local rp = ""

	local err, rply,  size = pHOST:read( rd_len, timeout )
	tbCONSOLE:AppendText( string.format ( "%x", string.byte(rply)).."\n")

	return rply
end -- getRply

-- Handle the button event

function OnGETCFG(event)
    openCOM_HOST()
    if ( pHOST ~= nil ) then
	sendCOM_HOST( string.char( 0x50) ) -- temperature
	local rpl0 = getRply()

	local t  = string.byte( rpl0 ) + 0
	
	local temperature = math.floor(( t  - 45 ))
	tbCONSOLE:AppendText( "temperature >"..temperature.."\n")

	sendCOM_HOST( string.char( 0x55) ) -- distance
	local d1 = string.byte( getRply() ) + 0
	local d0 = string.byte( getRply() ) + 0

	tbCONSOLE:AppendText( "d0 >"..d0.."< d1 >"..d1.."<".."\n")

	local distance = ( d1*256 + d0 )

	if ( distance < 10000 ) then
		local dcm = distance / 10
		tbCONSOLE:AppendText( "distance >" ..dcm.."\n")
	else
		tbCONSOLE:AppendText( "distance > err\n")
	end
	closeCOM_HOST()
   end
end -- OnTest(event)
