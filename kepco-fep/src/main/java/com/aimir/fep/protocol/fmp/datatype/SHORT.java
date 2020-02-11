package com.aimir.fep.protocol.fmp.datatype;

import org.apache.mina.core.buffer.IoBuffer;

import com.aimir.util.DataUtil;

public class SHORT extends FMPVariable
{
    private short value = (short)0;

    /**
     * constructor
     */
    public SHORT()
    {
    }

    /**
     * constructor
     *
     * @param value <code>short</code> value
     */
    public SHORT(short value)
    {
        this.value = value;
    }

    /**
     * constructor
     *
     * @param value <code>byte[]</code> value
     */
    public SHORT(byte[] value)
    {
        int f = ((value[0] & 0xff) << 8)
            + ((value[1]) & 0xff);
        this.value = (short)(f & 0xffff);
    }

    /**
     * get int value
     *
     * @return result <code>short</code> value
     */
    public short getValue()
    {
        return this.value;
    }

    /**
     * set int value
     *
     * @param result <code>short</code> value
     */
    public void setValue(short value)
    {
        this.value = value;
    }

    /**
     * set int value
     *
     * @param result <code>byte[]</code> value
     */
    public void setValue(byte[] value)
    {
        int f = ((value[0] & 0xff) << 8)
            + ((value[1]) & 0xff);
        this.value = (short)(f & 0xffff);
    }

    /**
     * encode SHORT Value
     *
     * @return value <code>byte[]</code> encoded byte array
     */
    public byte[] encode()
    {
        byte[] bval = new byte[2];
        bval[0] = (byte)((this.value & 0xffff) >> 8);
        bval[1] = (byte)(this.value & 0xffff);
        DataUtil.convertEndian(bval);
        return bval;
    }

    /**
     * decode SHORT Value
     *
     * @param buff <code>IoBuffer</code> input bytebuffer
     * @param size <code>int</code> Value length
     */
    public void decode(String ns, IoBuffer buff,int size)
    {
        byte[] bx = new byte[2];
        buff.get(bx,0,bx.length);
        DataUtil.convertEndian(bx);
        setValue(bx);
    }

    public int decode(String ns, byte[] buff,int pos)
    {
        byte[] bx = new byte[2];
        System.arraycopy(buff,pos,bx,0,bx.length);
        DataUtil.convertEndian(bx);
        setValue(bx);
        return bx.length;
    }

    public int decode(String ns, byte[] buff,int pos,int size)
    {
        byte[] bx = new byte[2];
        System.arraycopy(buff,pos,bx,0,bx.length);
        DataUtil.convertEndian(bx);
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
        return DataType.SHORT;
    }

    /**
     * get java syntax
     *
     *@returnsyntax<code>String</code>
     */
    public String getJavaSyntax()
    {
        return Short.class.getName();
    }
    public String getMIBName() { return "shortEntry"; }

    /**
     * get SHORT String Value
     *
     * @return value <code>String</code>
     */
    public String toString()
    {
        return Short.toString(this.value);
    }
}
