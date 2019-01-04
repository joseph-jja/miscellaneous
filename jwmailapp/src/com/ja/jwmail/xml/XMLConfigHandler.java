package com.ja.jwmail.xml;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import com.ja.jwmail.formbeans.AuthenticationRecord;

public class XMLConfigHandler extends DefaultHandler {
	
	// local copy of an authentication record
	private AuthenticationRecord authRecord;

	private String currentElement = "";
	
	public void  startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {

		// we have no attributes so 
		this.currentElement = qName;
	}
	
	public void characters(char[] ch, int start, int length) throws SAXException {

		String tempString = new String(ch,start,length);
		
		if ( currentElement.equals("pop3server") ) {
			authRecord.setPop3MailServer(tempString);
		} else if ( currentElement.equals("pop3port") ) {
			authRecord.setPop3Port(Integer.parseInt(tempString));
		} else if ( currentElement.equals("apop") ) {
			authRecord.setApop(Boolean.parseBoolean(tempString));
		} else if ( currentElement.equals("smtptls") ) {
			authRecord.setTls(Boolean.parseBoolean(tempString));
		} else if ( currentElement.equals("smtpssl") ) {
			authRecord.setSsl(Boolean.parseBoolean(tempString));
		} else if ( currentElement.equals("smtpauth") ) {
			authRecord.setSmtpauth(Boolean.parseBoolean(tempString));
		} else if ( currentElement.equals("smtpserver") ) {
			authRecord.setSmtpMailServer(tempString);
		} else if ( currentElement.equals("maildomainname") ) {
			authRecord.setMaildomainname(tempString);
		} else if ( currentElement.equals("smtpport") ) {
			authRecord.setSmtpPort(Integer.parseInt(tempString));
		}
		
	}
	
	public void endElement(String uri, String localName,String qName) throws SAXException {
		this.currentElement = "";
	}

	/**
	 * @param autRecord the autRecord to set
	 */
	public void setAuthRecord(AuthenticationRecord autRecord) {
		this.authRecord = autRecord;
	}

	/**
	 * @return the autRecord
	 */
	public AuthenticationRecord getAuthRecord() {
		return authRecord;
	}

}
