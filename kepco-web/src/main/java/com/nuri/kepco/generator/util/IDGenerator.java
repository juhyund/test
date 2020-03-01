package com.nuri.kepco.generator.util;

/**
 * An interface for database ID generators.
 *
 * @author Sebastian Schaffert (sschaffert@apache.org)
 */
public interface IDGenerator {

    /**
     * Return the next unique id for the type with the given name using the generator's id generation strategy.
     * @return
     */
    long getId();

    /**
     * Shut down this id generator, performing any cleanups that might be necessary.
     *
     */
    void shutdown();
}