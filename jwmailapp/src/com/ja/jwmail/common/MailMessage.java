package com.ja.jwmail.common;

import java.util.Date;
import java.util.Enumeration;
import java.util.List;

import javax.mail.Header;

public class MailMessage { 

    private Enumeration<Header> fullHeaders;
    private List<Pair<String, Object>> attachments;
    private String from; 
    private String subject; 
    private Date sentDate;
    private String messageType; 
    private String messageText;
    private boolean readMail;
    private boolean deleteMail;
    private int messageID;
    
	/**
	 * @param fullHeaders the fullHeaders to set
	 */
	public void setFullHeaders(Enumeration<Header> fullHeaders) {
		this.fullHeaders = fullHeaders;
	}
	/**
	 * @return the fullHeaders
	 */
	public Enumeration<Header> getFullHeaders() {
		return fullHeaders;
	}
	/**
	 * @param from the from to set
	 */
	public void setFrom(String from) {
		this.from = from;
	}
	/**
	 * @return the from
	 */
	public String getFrom() {
		return from;
	}
	/**
	 * @param subject the subject to set
	 */
	public void setSubject(String subject) {
		this.subject = subject;
	}
	/**
	 * @return the subject
	 */
	public String getSubject() {
		return subject;
	}
	/**
	 * @param sentDate the sentDate to set
	 */
	public void setSentDate(Date sentDate) {
		this.sentDate = sentDate;
	}
	/**
	 * @return the sentDate
	 */
	public Date getSentDate() {
		return sentDate;
	}
	/**
	 * @param messageType the messageType to set
	 */
	public void setMessageType(String messageType) {
		this.messageType = messageType;
	}
	/**
	 * @return the messageType
	 */
	public String getMessageType() {
		return messageType;
	}
	/**
	 * @param messageText the messageText to set
	 */
	public void setMessageText(String messageText) {
		this.messageText = messageText;
	}
	/**
	 * @return the messageText
	 */
	public String getMessageText() {
		return messageText;
	}
	/**
	 * @param readMail the readMail to set
	 */
	public void setReadMail(boolean readMail) {
		this.readMail = readMail;
	}
	/**
	 * @return the readMail
	 */
	public boolean isReadMail() {
		return readMail;
	}
	/**
	 * @param messageID the messageID to set
	 */
	public void setMessageID(int messageID) {
		this.messageID = messageID;
	}
	/**
	 * @return the messageID
	 */
	public int getMessageID() {
		return messageID;
	}
	/**
	 * @param deleteMail the deleteMail to set
	 */
	public void setDeleteMail(boolean deleteMail) {
		this.deleteMail = deleteMail;
	}
	/**
	 * @return the deleteMail
	 */
	public boolean isDeleteMail() {
		return deleteMail;
	}
	/**
	 * @param attachements the attachments to set
	 */
	public void setAttachments(List<Pair<String, Object>> attachments) {
		this.attachments = attachments;
	}
	/**
	 * @return the attachments
	 */
	public List<Pair<String, Object>> getAttachments() {
		return attachments;
	}

}
