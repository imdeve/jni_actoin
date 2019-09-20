package com.wenwp.threadpoolcallback;

public class SdkCli {

      public native static  void  sendCallback();



      public native static  void  addCallbackTask(RequestCallback  request);



















        public  static  void  doLog(String type,String msg)
        {
            System.out.println("logType:" + type + "   content:"+msg);

        }
}
