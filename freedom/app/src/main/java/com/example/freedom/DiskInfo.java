package com.example.freedom;

public class DiskInfo {
    public  String name;
    public   int  serial;

    public DiskInfo(){
        System.out.println("CCCCCCCCCCC:DiskIn");
    }

    public DiskInfo(String n,int s){
        this.name =n;
        this.serial =s;
        System.out.println("CCCCCCCCCCC:DiskInfo(String n,int s):this.name "+this.name+" ---this.serial:" +this.serial);
    }
}
