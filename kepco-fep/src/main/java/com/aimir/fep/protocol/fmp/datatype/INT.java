package com.aimir.fep.protocol.fmp.datatype;

import org.apache.mina.core.buffer.IoBuffer;

import com.aimir.util.DataUtil;

public class INT extends FMPVariable
{
    private int value = 0;

    /**
     * constructor
     */
    public INT()
    {
    }

    /**
     * constructor
     *
     * @param value <code>int</code> value
     */
    public INT(int value)
    {
        this.value = value;
    }

    /**
     * constructor
     *
     * @param value <code>byte</code> byte value
     */
    public INT(byte[] value)
    {
        this.value = ((value[0] & 0xff) << 24)
            + ((value[1] & 0xff) << 16)
            + ((value[2] & 0xff) << 8)
            + ((value[3] & 0xff) << 0); 
    }

    /**
     * get int value
     *
     * @return result <code>int</code> value
     */
    public int getValue()
    {
        return this.value;
    }

    /**
     * set value
     *
     * @param value <code>int</code>
     */
    public void setValue(int value)
    {
        this.value = value;
    }

    /**
     * set value
     *
     * @param value <code>byte[]</code>
     */
    public void setValue(byte[] value)
    {
        this.value = ((value[0] & 0xff) << 24)
            + ((value[1] & 0xff) << 16)
            + ((value[2] & 0xff) << 8)
            + ((value[3] & 0xff) << 0); 
    }

    /**
     * encode INT Value
     *
     * @return value <code>byte[]</code> encoded byte array
     */
    public byte[] encode()
    {
        byte[] bval = new byte[4];

        bval[0] = (byte)(this.value >> 24);
        bval[1] = (byte)(this.value >> 16);
        bval[2] = (byte)(this.value >> 8);
        bval[3] = (byte)(this.value);

        DataUtil.convertEndian(bval);

        return bval;
    }

    /**
     * decode INT Value
     *
     * @param buff <code>IoBuffer</code> input bytebuffer
     * @param size <code>int</code> Value length
     */
    public void decode(String ns, IoBuffer buff,int size)
    {
        byte[] bx = new byte[4];
        buff.get(bx,0,bx.length);

        DataUtil.convertEndian(bx);
        setValue(bx);
    }

    public int decode(String ns, byte[] buff,int pos)
    {
        byte[] bx = new byte[4];
        System.arraycopy(buff,pos,bx,0,bx.length);
        DataUtil.convertEndian(bx);
        setValue(bx);
        return bx.length;
    }

    public int decode(String ns, byte[] buff,int pos,int size)
    {
        byte[] bx = new byte[4];
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
        return DataType.INT;
    }

    /**
     * get java syntax
     *
     *@returnsyntax<code>String</code>
     */
    public String getJavaSyntax()
    {
        return Integer.class.getName();
    }
    public String getMIBName() { return "intEntry"; }

    /**
     * get INT String Value
     *
     * @return value <code>String</code>
     */
    public String toString()
    {
        return Integer.toString(this.value);
    }
}
