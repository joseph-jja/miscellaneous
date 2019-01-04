package com.ja.jwmail.formbeans;

import com.ja.jwmail.common.MailMessage;

/**
 * this is the class that shows the list of messages on a screen
 * in a table 
 * 
 * @author Joseph Acosta
 *
 */
public class MailboxMessage extends BaseFormBean { 

    private MailMessage message;
    private int index;

	/**
	 * @param message the message to set
	 */
	public void setMessage(MailMessage message) {
		this.message = message;
	}

	/**
	 * @return the message
	 */
	public MailMessage getMessage() {
		return message;
	}

	/**
	 * @param index the index to set
	 */
	public void setIndex(int index) {
		this.index = index;
	}

	/**
	 * @return the index
	 */
	public int getIndex() {
		return index;
	}
}

