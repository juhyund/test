package com.aimir.fep.protocol.fmp.datatype;

import org.apache.mina.core.buffer.IoBuffer;

public abstract class FMPNonFixedVariable extends FMPVariable
{
    protected byte[] value = null; 
    protected int len = 0;
    protected boolean isFixed = false;


    /**
     * get value length
     *
     * @return length <code>int</code>
     */
    public final int getLen()
    {
        return this.len;
    }
    /**
     * set value length
     *
     * @param length <code>int</code>
     */
    public final void setLen(int len)
    {
        this.value = new byte[len];
        this.len = len;
    }

    /**
     * check whether variable is fixed or not fixed
     *
     * @return result <code>boolean</code>
     */
    public boolean getIsFixed()
    {
        return this.isFixed;
    }
    /**
     * set fixed variable
     *
     * @param isFixed <code>boolean</code>
     */
    public void setIsFixed(boolean isFixed)
    {
        this.isFixed = isFixed;
    }

    /**
     * encode
     *
     * @param isCompact <code>boolean</code>
     */
    public abstract byte[] encode(boolean isCompact);
    /**
     * decode
     *
     * @param buff <code>IoBuffer</code>
     */
    public abstract void decode(String ns, IoBuffer buff);
}
