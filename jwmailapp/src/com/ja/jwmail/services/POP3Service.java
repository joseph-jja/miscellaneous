package com.ja.jwmail.services; 

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Properties;

import javax.activation.DataHandler;
import javax.mail.Address;
import javax.mail.BodyPart;
import javax.mail.Flags;
import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.Part;
import javax.mail.Session;
import javax.mail.Store;

import com.ja.jwmail.common.MailMessage;
import com.ja.jwmail.common.Pair;

/** 
 * wrapper class for the pop mail service 
 *
 * @author Joseph Acosta
 */
public class POP3Service { 

    private String username;
    private String password;
    private String serverName;
    private int port = 110;    // default port is 110
    private boolean connected = false;
    private boolean apop = false;

    private Store store=null;
    private Folder folder=null;
    private Properties props = null;
    private Session session = null;
    private Message[] msgs = null;
    
    private class MessageContent {
    	
    	public String messageContent;
    	public String messageType;
    	    	
    }

    /**
     * connect using the default port for pop3 of 110 
     * apop is false
     * username and password are passed in as well as pop3 server name
     * 
     * @param username
     * @param passwd
     * @param serverName
     * @return
     * @throws Exception
     */
    public boolean connect(String username, String passwd, 
         String serverName) throws Exception {

        return this.connect(username, passwd, serverName, this.port);
    }

    /**
     * connect and specify the pop3 port and apop is false
     * 
     * @param username
     * @param passwd
     * @param serverName
     * @param port
     * @return
     * @throws Exception
     */
    public boolean connect(String username, String passwd, 
         String serverName, int port) throws Exception {

        return this.connect(username, passwd, serverName, this.port, false);
    }

    /**
     * connect with apop and pop3 port specified
     * 
     * @param username
     * @param passwd
     * @param serverName
     * @param port
     * @param apop
     * @return
     * @throws Exception
     */
    public boolean connect(String username, String passwd, 
         String serverName, int port, boolean apop) throws Exception {

        // set local props 
        this.username = username;  
        this.password = passwd;  
        this.serverName = serverName;  
        this.port = port;  
        this.apop = apop;  

        // -- Get hold of the default session --
        this.props = System.getProperties();
        this.props.put("mail.pop3.port", Integer.toString(this.port) );
        this.props.put("mail.pop3.apop.enable", Boolean.toString(this.apop) );

        this.session = Session.getDefaultInstance(props, null);

        // -- Get hold of a POP3 message store, and connect to it --
        this.store = session.getStore("pop3");

        // connect to the pop mail server
        store.connect(this.serverName, this.username, this.password);
       
        // -- Try to get hold of the default folder --
        Folder defFolder = store.getDefaultFolder();
        if (defFolder == null) throw new Exception("No default folder");
        
        // -- ...and its the INBOX --
        folder = defFolder.getFolder("INBOX");
        if (folder == null) throw new Exception("No POP3 INBOX");
       
        // -- Open the folder for read write --
        folder.open(Folder.READ_WRITE); 

        // -- Get the message wrappers and process them --
        msgs = folder.getMessages();
        
        this.connected = true; // we are connected, otherwise we threw an exception

        return this.isConnected();
    }

    /**
     * is the service connected 
     * 
     * @return
     */
    public boolean isConnected() { 
        return this.connected;
    } 
    
    /**
     * disconnect from the server
     * 
     * @throws Exception
     */
    public void disconnect() throws Exception { 
        if ( this.isConnected() ) { 
           if ( this.folder.isOpen() ) {
                this.folder.close(true);
            }
            if ( this.store.isConnected()){
                this.store.close();
            }
        }
    }

    /** 
     * get the number of messages
     * 
     * @return
     */
    public int getMessageCount() { 
        return this.msgs.length;
    }

    /** 
     * set the delete flag on a message and the folder
     * 
     * @param index
     * @return
     * @throws Exception
     */
    public boolean deleteMessage(int index) throws Exception { 

        if ( index > msgs.length || index < 0 ) { 
           throw new Exception("Index out of bounds exception! For index (" + index + ").");
        }
        this.msgs[index].setFlag(Flags.Flag.DELETED, true);    
        Flags flag = this.msgs[index].getFlags();
        int fldrmsg = index + 1;
        this.folder.setFlags(fldrmsg, fldrmsg, flag, true);
        return true;
    }
       
    /**
     * Return the primary text content of the message.
     * taken from the javamail FAQ
     * I added the comments in here though
     * this method uses recursion 
     */
    private MessageContent getTextContent(Part messagePart) throws MessagingException, IOException {
        
    	// here we do a check to see if the content type is text/something
    	// if it is then we return the text as that is what we want
    	if (messagePart.isMimeType("text/*")) {
            String content= (String)messagePart.getContent();
            MessageContent mc = new MessageContent();
            mc.messageContent = content;
            mc.messageType = messagePart.getContentType();
            return mc;
        }

        if (messagePart.isMimeType("multipart/alternative")) {
            // prefer html text over plain text
        	Multipart msgPart = (Multipart)messagePart.getContent();
        	MessageContent mc = null;
            for (int i = 0; i < msgPart.getCount(); i++) {
                BodyPart bp = msgPart.getBodyPart(i);
                if (bp.isMimeType("text/plain")) {
                    if (mc == null) {
                    	mc = getTextContent(bp);
                    }
                    continue;
                } else if (bp.isMimeType("text/html")) {
                	MessageContent content = getTextContent(bp);
                    if (content != null && content.messageContent != null)
                        return content;
                } else {
                    return getTextContent(bp);
                }
            }
            return mc;
        } else if (messagePart.isMimeType("multipart/*")) {
            Multipart msgPart = (Multipart)messagePart.getContent();
            for (int i = 0; i < msgPart.getCount(); i++) {
            	BodyPart bp = msgPart.getBodyPart(i);
            	MessageContent content = getTextContent(bp);
            	if (content != null && content.messageContent != null)
                    return content;
            }
        }
        return null;
    }


    /**
     * get message at index
     * currently attachments are not handled
     * 
     * @param index
     * @return
     * @throws MessagingException
     * @throws Exception
     */
    @SuppressWarnings("unchecked")
    public MailMessage getMessage(int index) throws MessagingException, Exception { 

        if ( index > msgs.length || index < 0 ) { 
           throw new Exception("Index out of bounds exception! For index (" + index + ").");
        }
        
        Message message = this.msgs[index];
        MailMessage mail = new MailMessage();
        
        // get the from 
        Address[] mailFrom = message.getFrom();
        if ( mailFrom != null && mailFrom.length > 0 ) {
            mail.setFrom(mailFrom[0].toString());
        }
        
        // get the subject
        String subject = message.getSubject();
        mail.setSubject(subject);
        
        // get the date
        Date sentDate = message.getSentDate();
        mail.setSentDate(sentDate);

        mail.setMessageID(message.getMessageNumber());
        
        mail.setFullHeaders(message.getAllHeaders());

        // now time to process the message
        Part messagePart = message;
        MessageContent content = getTextContent(messagePart);
        if ( content != null ) { 
        	mail.setMessageText(content.messageContent);
            mail.setMessageType(content.messageType);
        } else {
            // this it the message type of the message part
            String type = messagePart.getContentType();
            mail.setMessageType(type);
        }
        
        // now look for attachments
        // this code could probably be optimized
        try {                 
            Multipart msgPart = (Multipart)message.getContent();
            List<Pair<String, Object>> attachments = new ArrayList<Pair<String, Object>>();
            for (int i = 0; i < msgPart.getCount(); i++) {
            	BodyPart bodyPart = msgPart.getBodyPart(i);
            	String disposition = bodyPart.getDisposition();
            	if ( disposition != null ) { 
            		// in this part we only care about attachments
            		if ( disposition.equals(Part.ATTACHMENT) ) {
            			DataHandler handler = bodyPart.getDataHandler();
            			InputStream instream = handler.getInputStream();
            			BufferedReader attachedFile = new BufferedReader(new InputStreamReader(instream));
            			Object data = new Object();
            			while (attachedFile.ready()) {
            				data = data + attachedFile.readLine();
            			}
            			attachedFile.close();
                        // attachment name is the key to the hash
            			// hopefully we wont have attachments with the same name
            			Pair<String, Object> attach = new Pair<String, Object>(handler.getName(), data);
            			attachments.add(attach);
            		}
            	}
            }
            // we have attachments so set them
            if ( ! attachments.isEmpty() ) {
            	mail.setAttachments(attachments);
            }
        } catch (ClassCastException ce) {
        	
        }
        
        
                
        return mail;
    }

    // we can use this for ajax stuff
    public boolean hasNewMessages() throws Exception { 
        return folder.hasNewMessages();
    }

    /**
     * get a list of the mail messages for an account
     * 
     * @return a List of MailMessage objects
     * @throws MessagingException
     * @throws Exception
     */
    public List<MailMessage> getMessages() throws MessagingException, Exception { 

        List<MailMessage> results = new ArrayList<MailMessage>();
        
        for ( int i = 0; i < this.msgs.length; i += 1 ) {

            MailMessage mail = this.getMessage(i);            
                    
            results.add(mail);            
        }
        
        return results;
    }
    
    /**
     * a simple method to get the list of all folders if they exist
     * probably more useful if this was imap but we have it here anyway
     * 
     * @return
     * @throws Exception
     */
    public Folder[] getAllFolders() throws Exception { 
    	
    	return this.folder.getParent().list();
    	
    }
}
