/**
 * @file PC_Handle.c
 * @brief  This file deals with interacting with the PC, send/ receive messages.  It
 *         also allows you to overwrite the modes used in the function
 * @author Alex Etling(petling)
 */

#include "Globals.h"


/**
 * @brief This fucntion reads the message in USART_PC_RecievedPacket. It determines
 *        its type and sends the appropriate message to PC
 *        The two possibilities are that you sent 'x' - PC_CMD_INIT - this just gets
 *        response from the system. The other message is 'M' - PC_CMD_NEWMODES
 *        this message type will change the mode file
 * @return bool    but does not seem to ever return, so it will return false?
 */
bool PC_parse_message()
{
  unsigned char MessageType;
  USART_PC_Message_ready=false;
  MessageType=USART_PC_ReceivedPacket[2];
  switch(MessageType)
  {
    case PC_CMD_INIT:
      USART_transmitStringToPCFromFlash(PSTR("SABT-v2.1"));
      TX_NEWLINE_PC;      
      break;
    case PC_CMD_NEWMODES:
      PC_RequestsToModifyModesFile();
      break;
    //incorrect message type
    default:
      PRINTF("SABT-INCORRECT MESSAGE TYPE!!!!");
      break;
  }
}

/**
 * @brief This function will replace the MODES.DAT file with new modes from the 
 *        message variable USART_PC_RecievedPacket.  
 *        The message size can at most be 20 charachters - WritingFileContent
 * @return Void
 */
void PC_RequestsToModifyModesFile(void)
{
  const char* ModesFile="MODES.DAT";
  unsigned char WritingFileContent[20];
  
  // Clear the buffer
  int iT=0;
  for(iT=0;iT<20;iT++)
  {
    WritingFileContent[iT]=0x00;
  }

  InitSDCard(false);

  // Copy over the modes in the form <1><2>...<n>. Ignoring the "PCM" header
  for(iT=3;iT<USART_PC_received_playload_len;iT++)
  {
    WritingFileContent[iT-3]=USART_PC_ReceivedPacket[iT];
  }

  DPRINTF("File content: %s\n", WritingFileContent);

  if(ReplaceTheContentOfThisFileWith(ModesFile,WritingFileContent)==0)
  {
    USART_transmitStringToPCFromFlash(PSTR("SABT-OK"));
    TX_NEWLINE_PC;      
  }else{
    USART_transmitStringToPCFromFlash(PSTR("SABT-FAIL"));
    TX_NEWLINE_PC;  
  }
}
