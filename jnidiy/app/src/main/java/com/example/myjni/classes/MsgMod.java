package com.example.myjni.classes;

public class MsgMod {


// int imSendTeamMsg(SendMsgReqData &reqData,ImSendMsgCallbackFunc cb)
    public native int  sendMsg(SendMsgReqData req ,CallFunc func);

}
