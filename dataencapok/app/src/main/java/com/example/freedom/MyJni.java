package com.example.freedom;

public class MyJni {

    public native void displayParms(String showText, int i, boolean bl);
    public native int add(int a, int b);
    public native void setArray(boolean[] blList);
    public native String[] getStringArray();
    public native DiskInfo getStruct();
    public native DiskInfo[] getStructArray();
    public native java.util.ArrayList<DiskInfo> getStructList();

    public static String testGo() {
        MyJni changeJni = new MyJni();

        changeJni.displayParms("Hello World!", 100, true);

        System.out.println("----------------------------");

        int ret = changeJni.add(12, 20);
        System.out.println("The result is: " + String.valueOf(ret));


        System.out.println("--------------------- --");
        boolean[] blList = new boolean[] { true, false, true };
        changeJni.setArray(blList);


        System.out.println("------------------");
        String[] strList = changeJni.getStringArray();
        for (int i = 0; i < strList.length; i++) {
            System.out.print(strList[i]);
        }

        System.out.println("------------ret struct-----------");

        DiskInfo disk = changeJni.getStruct();
        System.out.println("name:" + disk.name);
        System.out.println("Serial:" + disk.serial);




        System.out.println("----------ret struct arr-----");
        DiskInfo[] diskList = changeJni.getStructArray();
        for (int i = 0; i < diskList.length; i++) {
            System.out.println("foreach -name:" + diskList[i].name);
            System.out.println("foreach - Serial:" + diskList[i].serial);
        }

        return  String.valueOf(ret);

        // return "end";
    }

}
