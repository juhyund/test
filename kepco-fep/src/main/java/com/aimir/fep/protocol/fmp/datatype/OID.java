package com.aimir.fep.protocol.fmp.datatype;

import org.apache.mina.core.buffer.IoBuffer;

import com.aimir.util.DataUtil;

public class OID extends FMPVariable
{
    public String value = "";

    /**
     * constructor
     */
    public OID()
    {
    }

    /**
     * constructor
     *
     * @param value <code>String</code> oid value
     */
    public OID(String value)
    {
        this.value = value;
    }

    /**
     * constructor
     *
     * @param value <code>byte[]</code> oid value
     */
    public OID(byte[] value)
    {
        this.value = DataUtil.getOIDString(value);
    }

    /**
     * get value
     *
     * @return result <code>String</code>
     */

    public String getValue()
    {
        return this.value;
    }

    /**
     * set value
     *
     * @param value <code>String</code> value
     */
    public void setValue(String value)
    {
        this.value = value;
    }

    /**
     * set value
     *
     * @param value <code>byte[]</code> value
     */
    public void setValue(byte[] value)
    {
        this.value = DataUtil.getOIDString(value);
    }

    /**
     * encode OID Value
     *
     * @return value <code>byte[]</code> encoded byte array
     */
    public byte[] encode()
    {
        if(this.value == null)
            return new byte[0];

        byte[] bval = new byte[3];
        String[] ids = this.value.split("[\\.]");
        for(int i = 0 ; i < ids.length ; i++)
        {
            bval[i] = DataUtil.getByteToInt(ids[i]);
        }
        return bval;
    }

    /**
     * decode OID Value
     *
     * @param buff <code>IoBuffer</code> input bytebuffer
     * @param size <code>int</code> Value length
     */
    public void decode(String ns, IoBuffer buff,int size)
    {
        byte[] bx = new byte[3];
        buff.get(bx,0,bx.length);
        setValue(bx);
    }

    public int decode(String ns, byte[] buff,int pos)
    {
        byte[] bx = new byte[3];
        System.arraycopy(buff,pos,bx,0,bx.length);
        setValue(bx);
        return bx.length;
    }

    public int decode(String ns, byte[] buff,int pos,int size)
    {
        byte[] bx = new byte[3];
        System.arraycopy(buff,pos,bx,0,bx.length);
        setValue(bx);
        return size;
    }

    /**
     * get syntax(data type)
     *
     * @return syntax <code>int</code> syntax
     */
    public int getSyntax()
    {
        return DataType.OID;
    }

    /**
     * get java syntax
     *
     *@returnsyntax<code>String</code>
     */
    public String getJavaSyntax()
    {
        return String.class.getName();
    }
    public String getMIBName() { return "oidEntry"; }

    /**
     * get INT String Value
     *
     * @return value <code>String</code>
     */
    public String toString()
    {
        return this.value;
    }
}
