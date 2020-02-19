package com.nuri.kepco.fep.mddata;

public interface IMeasurementData
{
    public MeterDataParser getMeterDataParser();
    
    public String getDeviceId();
    
    public String getTimeStamp();
}