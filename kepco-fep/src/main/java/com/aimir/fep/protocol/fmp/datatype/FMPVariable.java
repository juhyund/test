package com.aimir.fep.protocol.fmp.datatype;

import org.apache.mina.core.buffer.IoBuffer;

public abstract class FMPVariable implements java.io.Serializable
{
    /**
     * encode
     *
     * @return result <code>byte[]</code>
     */
    public abstract byte[] encode();
    /**
     * decode
     *
     * @param buff <code>IoBuffer</code>
     * @param size <code>int</code>
     */
    public abstract void decode(String ns,IoBuffer buff,int size);

    public abstract int decode(String ns,byte[] buff,int pos);
    public abstract int decode(String ns,byte[] buff,int pos,int size);

    /**
     * get syntax
     *
     * @return syntax <code>int</code>
     */
    public abstract int getSyntax();

    /**
     * get java syntax
     *
     * @return syntax <code>String</code>
     */
    public abstract String getJavaSyntax();

    public abstract String getMIBName();

    /**
     * get syntax string
     *
     * @return syntax <code>int</code>
     */
    public final String getSyntaxString()
    {
        String clsname = getClass().getName();
        int idx = clsname.lastIndexOf(".");
        return clsname.substring(idx+1,clsname.length());
    }

    /**
     * get String
     *
     * @return result <code>String</code>
     */
    public abstract String toString();


    /**
     * get FMP Variable Object according to specified data type
     *
     * @param  type <code>String</code> data type
     * @return variable <code>FMPVariable</code>
     */
    public final static FMPVariable getFMPVariableObject(String type)
    {
        String pre = "com.aimir.fep.protocol.fmp.datatype.";
        if(type.toUpperCase().equals("STRING")
                || type.toUpperCase().equals("STREAM"))
        {
            type="OCTET";
        }
        try {
        Class cls = Class.forName(pre+type.toUpperCase());
        return (FMPVariable)cls.newInstance();
        }catch(Exception ex)
        {
            ex.printStackTrace();
            return null;
        }
    }

    /**
     * get FMP Variable Object according to specified data type
     *
     * @param  type <code>int</code> data type
     * @return variable <code>FMPVariable</code>
     */
    public final FMPVariable getFMPVariableObject(int type)
    { 
        if(type == DataType.BOOL) 
            return new BOOL();
        else if(type == DataType.BYTE)
            return new BYTE();
        else if(type == DataType.WORD)
            return new WORD();
        else if(type == DataType.UINT)
            return new UINT();
        else if(type == DataType.CHAR)
            return new CHAR();
        else if(type == DataType.SHORT)
            return new SHORT();
        else if(type == DataType.INT)
            return new INT();
        else if(type == DataType.BCD)
            return new BCD();
        else if(type == DataType.VER)
            return new VER();
        else if(type == DataType.HEX)
            return new HEX();
        else if(type == DataType.STRING)
            return new OCTET();
        else if(type == DataType.STREAM)
            return new OCTET();        
        else if(type == DataType.OID)
            return new OID();
        else if(type == DataType.IPADDR)
            return new IPADDR();        
        else if(type == DataType.TIMESTAMP)
            return new TIMESTAMP();
        else if(type == DataType.TIMEDATE)
            return new TIMEDATE();

        return null;
    }

}
