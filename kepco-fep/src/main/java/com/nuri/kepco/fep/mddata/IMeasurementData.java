package com.nuri.kepco.fep.mddata;

public interface IMeasurementData
{
    public DataParser getMeterDataParser();
    
    public String getDeviceId();
    
    public String getModemTime();
    
}

