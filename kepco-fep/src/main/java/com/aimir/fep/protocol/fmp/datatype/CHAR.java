package com.aimir.fep.protocol.fmp.datatype;

import org.apache.mina.core.buffer.IoBuffer;

public class CHAR extends FMPVariable
{
    private char value = 0x00;

    /**
     * constructor
     */
    public CHAR()
    {
    }

    /**
     * constructor
     *
     * @param value <code>char</code> char value
     */
    public CHAR(char value)
    {
        this.value = value;
    }

    /**
     * constructor
     *
     * @param value <code>byte</code> char byte value
     */
    public CHAR(byte value)
    {
        this.value = (char)(value & 0xff);
    }

    /**
     * get char value
     *
     * @return result <code>char</code>
     */
    public char getValue()
    {
        return this.value;
    }

    /**
     * set char value
     *
     * @param value <code>char</code>
     */
    public void setValue(char value)
    {
        this.value = value;
    }

    /**
     * set char value
     *
     * @param value <code>byte</code>
     */
    public void setValue(byte value)
    {
        this.value = (char)(value & 0xff);
    }

    /**
     * encode CHAR Value
     *
     * @return value <code>byte[]</code> encoded byte array
     */
    public byte[] encode()
    {
        byte[] bval = new byte[1];
        bval[0] = (byte)this.value;
        return bval;
    }

    /**
     * decode BYTE Value
     *
     * @param buff <code>IoBuffer</code> input bytebuffer
     * @param size <code>int</code> Value length
     */
    public void decode(String ns, IoBuffer buff,int size)
    {
        setValue(buff.get());
    }
    public int decode(String ns, byte[] buff,int pos)
    {
        setValue(buff[pos]);
        return 1;
    }

    public int decode(String ns, byte[] buff,int pos,int size)
    {
        setValue(buff[pos]);
        return size;
    }

    /**
     * get syntax(data type)
     *
     * @return syntax <code>int</code> syntax
     */
    public int getSyntax()
    {
        return DataType.CHAR;
    }

    /**
     * get java syntax
     *
     *@returnsyntax<code>String</code>
     */
    public String getJavaSyntax()
    {
        return Character.class.getName();
    }

    public String getMIBName() { return "charEntry"; }

    /**
     * get CHAR String Value
     *
     * @return value <code>String</code>
     */
    public String toString()
    {
        return Character.toString(value);
    }
}

