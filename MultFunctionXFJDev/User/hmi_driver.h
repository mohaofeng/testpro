/*! 
 *  \file hmi_driver.h
 *  \brief �����������ļ�
 *  \version 1.0
 *  \date 2012-2015
 *  \copyright ���ݴ�ʹ��Ƽ����޹�˾
 */

#ifndef _HMI_DRIVER_
#define _HMI_DRIVER_

#define CRC16_ENABLE 0         /*!< �����ҪCRC16У�鹦�ܣ��޸Ĵ˺�Ϊ1(��ʱ��Ҫ��VisualTFT��������CRCУ��)*/

#include "bsp_usart1.h"
#include "ScreenDef.h"




#define  START_FONT   	 				6   		//��������ʱ��ʾ����
#define  SYS_TMP_FONT 	 				6				//����ϵͳ��Ϣ��ʾ����
#define  ASCII_06X12  					0				//����ϵͳ��Ϣ��ʾ����
#define  ASCII_08X12  					1				//����ϵͳ��Ϣ��ʾ����
#define  ASCII_12X24  					2				//����ϵͳ��Ϣ��ʾ����
#define  ASCII_16X32  					3				//����ϵͳ��Ϣ��ʾ����
#define  GBK_12X12  						4				//����ϵͳ��Ϣ��ʾ����
#define  GBK_16X16  						5				//����ϵͳ��Ϣ��ʾ����
#define  GBK_24X24  						6				//����ϵͳ��Ϣ��ʾ����
#define  GBK_32X32							7				//����ϵͳ��Ϣ��ʾ����
#define  GBK_32X64							8				//����ϵͳ��Ϣ��ʾ����
#define  GBK_64X64							9				//����ϵͳ��Ϣ��ʾ����
#define  SYS_LOG_FONT  					1				//����ϵͳ��Ϣ��ʾ����
#define  ASCII8X16  						1				//����ϵͳ��Ϣ��ʾ����
#define  X_START_pos   					40  		//����ϵͳ��ʾ��Ϣx��ʼ����
#define  Y_gas  								30  		//����ϵͳ��ʾ��Ϣy����



#define  TOOL_BAR_FONT 	 				GBK_16X16				//����ϵͳ��Ϣ��ʾ����


#define  TEST_WIFI_Y_POS 		 	20  
#define  TEST_WIFI_X_OK_POS 	300

#define  SET_MOD_Y_POS  			50
#define  SET_NOACK_POS  			80
#define  CONNECT_AP_Y_POS  		110
#define  CONNECT_SER_Y_POS  	140
#define  SET_TAR_Y_POS  			170
#define  START_TAR_Y_POS  		200

#define  TMP_COLO  						0X1

/*! 
 *  \brief  ��������Ƿ����CRC16У��
 *  \param buffer ��У������ݣ�ĩβ�洢CRC16
 *  \param n ���ݳ��ȣ�����CRC16
 *  \return У��ͨ������1�����򷵻�0
 */
uint16_t CheckCRC16(uint8_t *buffer,uint16_t n);

/*! 
 *  \brief  ��ʱ
 *  \param  n ��ʱʱ��(���뵥λ)
 */
void DelayMS(unsigned int n);

/*! 
 *  \brief  �����豸���ã�����֮����Ҫ�����������޸Ĳ����ʡ���������������������ʽ
 */
void LockDeviceConfig(void);

/*! 
 *  \brief  �����豸����
 */
void UnlockDeviceConfig(void);

/*! 
 *  \brief     �޸Ĵ������Ĳ�����
 *  \details  ������ѡ�Χ[0~14]����Ӧʵ�ʲ�����
                   {1200,2400,4800,9600,19200,38400,57600,115200,1000000,2000000,218750,437500,875000,921800,2500000}
 *  \param  option ������ѡ��
 */
void SetCommBps(uint8_t option);

/*! 
 *  \brief  ������������
 */
void SetHandShake(void);

/*! 
 *  \brief  ����ǰ��ɫ
 *  \param  color ǰ��ɫ
 */
void SetFcolor(uint16_t color);

/*! 
 *  \brief  ���ñ���ɫ
 *  \param  color ����ɫ
 */
void SetBcolor(uint16_t color);

/*! 
 *  \brief  �������
 */
void GUI_CleanScreen(void);

/*! 
 *  \brief  �������ּ��
 *  \param  x_w ������
  *  \param  y_w ������
 */
void SetTextSpace(uint8_t x_w, uint8_t y_w);

/*! 
 *  \brief  ����������ʾ����
 *  \param  enable �Ƿ���������
 *  \param  width ���
 *  \param  height �߶�
 */
void SetFont_Region(uint8_t enable,uint16_t width,uint16_t height );

/*! 
 *  \brief  ���ù���ɫ
 *  \param  fillcolor_dwon ��ɫ�½�
 *  \param  fillcolor_up ��ɫ�Ͻ�
 */
void SetFilterColor(uint16_t fillcolor_dwon, uint16_t fillcolor_up);

/*! 
 *  \brief  ���ù���ɫ
 *  \param  x λ��X����
 *  \param  y λ��Y����
 *  \param  back ��ɫ�Ͻ�
 *  \param  font ����
 *  \param  strings �ַ�������
 */
void DisText(uint16_t x, uint16_t y,uint8_t back,uint8_t font,uint8_t *strings );

/*! 
 *  \brief    ��ʾ���
 *  \param  enable �Ƿ���ʾ
 *  \param  x λ��X����
 *  \param  y λ��Y����
 *  \param  width ���
 *  \param  height �߶�
 */
void DisCursor(uint8_t enable,uint16_t x, uint16_t y,uint8_t width,uint8_t height );

/*! 
 *  \brief      ��ʾȫ��ͼƬ
 *  \param  image_id ͼƬ����
 *  \param  masken �Ƿ�����͸������
 */
void DisFull_Image(uint16_t image_id,uint8_t masken);

/*! 
 *  \brief      ָ��λ����ʾͼƬ
 *  \param  x λ��X����
 *  \param  y λ��Y����
 *  \param  image_id ͼƬ����
 *  \param  masken �Ƿ�����͸������
 */
void DisArea_Image(uint16_t x,uint16_t y,uint16_t image_id,uint8_t masken);

/*! 
 *  \brief      ��ʾ�ü�ͼƬ
 *  \param  x λ��X����
 *  \param  y λ��Y����
 *  \param  image_id ͼƬ����
 *  \param  image_x ͼƬ�ü�λ��X����
 *  \param  image_y ͼƬ�ü�λ��Y����
 *  \param  image_l ͼƬ�ü�����
 *  \param  image_w ͼƬ�ü��߶�
 *  \param  masken �Ƿ�����͸������
 */
void DisCut_Image(uint16_t x,uint16_t y,uint16_t image_id,uint16_t image_x,uint16_t image_y,
                   uint16_t image_l, uint16_t image_w,uint8_t masken);

/*! 
 *  \brief      ��ʾGIF����
 *  \param  x λ��X����
 *  \param  y λ��Y����
 *  \param  flashimage_id ͼƬ����
 *  \param  enable �Ƿ���ʾ
 *  \param  playnum ���Ŵ���
 */
void DisFlashImage(uint16_t x,uint16_t y,uint16_t flashimage_id,uint8_t enable,uint8_t playnum);

/*! 
 *  \brief      ����
 *  \param  x λ��X����
 *  \param  y λ��Y����
 */
void GUI_Dot(uint16_t x,uint16_t y);

/*! 
 *  \brief      ����
 *  \param  x0 ��ʼλ��X����
 *  \param  y0 ��ʼλ��Y����
 *  \param  x1 ����λ��X����
 *  \param  y1 ����λ��Y����
 */
void GUI_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

/*! 
 *  \brief      ������
 *  \param  mode ģʽ
 *  \param  dot ���ݵ�
 *  \param  dot_cnt ����
 */
void GUI_ConDots(uint8_t mode,uint16_t *dot,uint16_t dot_cnt);

/*! 
 *  \brief      ������Բ
 *  \param  x0 Բ��λ��X����
 *  \param  y0 Բ��λ��Y����
 *  \param  r �뾶
 */
void GUI_Circle(uint16_t x0, uint16_t y0, uint16_t r);

/*! 
 *  \brief      ��ʵ��Բ
 *  \param  x0 Բ��λ��X����
 *  \param  y0 Բ��λ��Y����
 *  \param  r �뾶
 */
void GUI_CircleFill(uint16_t x0, uint16_t y0, uint16_t r);

/*! 
 *  \brief      ������
 *  \param  x0 Բ��λ��X����
 *  \param  y0 Բ��λ��Y����
 *  \param  r �뾶
 *  \param  sa ��ʼ�Ƕ�
 *  \param  ea ��ֹ�Ƕ�
 */
void GUI_Arc(uint16_t x,uint16_t y, uint16_t r,uint16_t sa, uint16_t ea);

/*! 
 *  \brief      �����ľ���
 *  \param  x0 ��ʼλ��X����
 *  \param  y0 ��ʼλ��Y����
 *  \param  x1 ����λ��X����
 *  \param  y1 ����λ��Y����
 */
void GUI_Rectangle(uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1 );

/*! 
 *  \brief      ��ʵ�ľ���
 *  \param  x0 ��ʼλ��X����
 *  \param  y0 ��ʼλ��Y����
 *  \param  x1 ����λ��X����
 *  \param  y1 ����λ��Y����
 */
void GUI_RectangleFill(uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1 );

/*! 
 *  \brief      ��������Բ
 *  \param  x0 ��ʼλ��X����
 *  \param  y0 ��ʼλ��Y����
 *  \param  x1 ����λ��X����
 *  \param  y1 ����λ��Y����
 */
void GUI_Ellipse (uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1 );

/*! 
 *  \brief      ��ʵ����Բ
 *  \param  x0 ��ʼλ��X����
 *  \param  y0 ��ʼλ��Y����
 *  \param  x1 ����λ��X����
 *  \param  y1 ����λ��Y����
 */
void GUI_EllipseFill (uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1 );

/*! 
 *  \brief      ����
 *  \param  x0 ��ʼλ��X����
 *  \param  y0 ��ʼλ��Y����
 *  \param  x1 ����λ��X����
 *  \param  y1 ����λ��Y����
 */
void SetBackLight(uint8_t light_level);

/*! 
 *  \brief   ����������
 *  \time  time ����ʱ��(���뵥λ)
 */
void SetBuzzer(uint8_t time);

/*! 
 *  \brief   ����������
 *  \param enable ����ʹ��
 *  \param beep_on ����������
 *  \param work_mode ��������ģʽ��0���¾��ϴ���1�ɿ����ϴ���2�����ϴ�����ֵ��3���º��ɿ����ϴ�����
 *  \param press_calibration �������������20��У׼��������0���ã�1����
 */
void SetTouchPaneOption(uint8_t enbale,uint8_t beep_on,uint8_t work_mode,uint8_t press_calibration);

/*! 
 *  \brief   У׼������
 */
void	CalibrateTouchPane(void);

/*! 
 *  \brief  ����������
 */
void TestTouchPane(void);

/*! 
 *  \brief      ���õ�ǰд��ͼ��
 *  \details  һ������ʵ��˫����Ч��(��ͼʱ������˸)��
 *  \details  uint8_t layer = 0;
 *  \details  WriteLayer(layer);    //����д���
 *  \details  ClearLayer(layer);    //ʹͼ���͸��
 *  \details  //���һϵ�л�ͼָ��
 *  \details  //DisText(100,100,0,4,"hello hmi!!!");
 *  \details  DisplyLayer(layer);  //�л���ʾ��
 *  \details  layer = (layer+1)%2;  //˫�����л�
 *  \see DisplyLayer
 *  \see ClearLayer
 *  \param  layer ͼ����
 */
void WriteLayer(uint8_t layer);

/*! 
 *  \brief      ���õ�ǰ��ʾͼ��
 *  \param  layer ͼ����
 */
void DisplyLayer(uint8_t layer);

/*! 
 *  \brief      ���ͼ�㣬ʹͼ����͸��
 *  \param  layer ͼ����
 */
void ClearLayer(uint8_t layer);

/*! 
 *  \brief  д���ݵ��������û��洢��
 *  \param  startAddress ��ʼ��ַ
 *  \param  length �ֽ���
 *  \param  _data ��д�������
 */
void WriteUserFlash(uint32_t startAddress,uint16_t length,uint8_t *_data);

/*! 
 *  \brief  �Ӵ������û��洢����ȡ����
 *  \param  startAddress ��ʼ��ַ
 *  \param  length �ֽ���
 */
void ReadUserFlash(uint32_t startAddress,uint16_t length);

/*! 
 *  \brief      ����ͼ��
 *  \param  src_layer ԭʼͼ��
 *  \param  dest_layer Ŀ��ͼ��
 */
void CopyLayer(uint8_t src_layer,uint8_t dest_layer);

/*! 
 *  \brief      ���õ�ǰ����
 *  \param  screen_id ����ID
 */
void SetScreen(uint16_t screen_id);

/*! 
 *  \brief      ��ȡ��ǰ����
 */
void GetScreen(void);

/*! 
 *  \brief     ����\���û������
 *  \details ����\����һ��ɶ�ʹ�ã����ڱ�����˸�����ˢ���ٶ�
 *  \details �÷���
 *	\details SetScreenUpdateEnable(0);//��ֹ����
 *	\details һϵ�и��»����ָ��
 *	\details SetScreenUpdateEnable(1);//��������
 *  \param  enable 0���ã�1����
 */
void SetScreenUpdateEnable(uint8_t enable);

/*! 
 *  \brief     ���ÿؼ����뽹��
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  focus �Ƿ�������뽹��
 */
void SetControlFocus(uint16_t screen_id,uint16_t control_id,uint8_t focus);

/*! 
 *  \brief     ��ʾ\���ؿؼ�
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  visible �Ƿ���ʾ
 */
void SetControlVisiable(uint16_t screen_id,uint16_t control_id,uint8_t visible);

/*! 
 *  \brief     ���ô����ؼ�ʹ��
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  enable �ؼ��Ƿ�ʹ��
 */
void SetControlEnable(uint16_t screen_id,uint16_t control_id,uint8_t enable);

/*! 
 *  \brief     ��ȡ�ؼ�ֵ
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void GetControlValue(uint16_t screen_id,uint16_t control_id);

/*! 
 *  \brief     ���ð�ť״̬
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  value ��ť״̬
 */
void SetButtonValue(uint16_t screen_id,uint16_t control_id,uint8_t value);

/*! 
 *  \brief     �����ı�ֵ
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  str �ı�ֵ
 */
void SetTextValue(uint16_t screen_id,uint16_t control_id,uint8_t *str);

/*! 
 *  \brief      ���ý���ֵ
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  value ��ֵ
 */
void SetProgressValue(uint16_t screen_id,uint16_t control_id,uint32_t value);

/*! 
 *  \brief     �����Ǳ�ֵ
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  value ��ֵ
 */
void SetMeterValue(uint16_t screen_id,uint16_t control_id,uint32_t value);

/*! 
 *  \brief      ���û�����
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  value ��ֵ
 */
void SetSliderValue(uint16_t screen_id,uint16_t control_id,uint32_t value);

/*! 
 *  \brief      ����ѡ��ؼ�
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  item ��ǰѡ��
 */
void SetSelectorValue(uint16_t screen_id,uint16_t control_id,uint8_t item);

/*! 
 *  \brief      ��ʼ���Ŷ���
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationStart(uint16_t screen_id,uint16_t control_id);

/*! 
 *  \brief      ֹͣ���Ŷ���
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationStop(uint16_t screen_id,uint16_t control_id);

/*! 
 *  \brief      ��ͣ���Ŷ���
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationPause(uint16_t screen_id,uint16_t control_id);

/*! 
 *  \brief     �����ƶ�֡
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  frame_id ֡ID
 */
void AnimationPlayFrame(uint16_t screen_id,uint16_t control_id,uint8_t frame_id);

/*! 
 *  \brief     ������һ֡
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationPlayPrev(uint16_t screen_id,uint16_t control_id);

/*! 
 *  \brief     ������һ֡
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void AnimationPlayNext(uint16_t screen_id,uint16_t control_id);

/*! 
 *  \brief     ���߿ؼ�-���ͨ��
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  channel ͨ����
 *  \param  color ��ɫ
 */
void GraphChannelAdd(uint16_t screen_id,uint16_t control_id,uint8_t channel,uint16_t color);

/*! 
 *  \brief     ���߿ؼ�-ɾ��ͨ��
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  channel ͨ����
 */
void GraphChannelDel(uint16_t screen_id,uint16_t control_id,uint8_t channel);

/*! 
 *  \brief     ���߿ؼ�-�������
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  channel ͨ����
 *  \param  pData ��������
 *  \param  nDataLen ���ݸ���
 */
void GraphChannelDataAdd(uint16_t screen_id,uint16_t control_id,uint8_t channel,uint8_t *pData,uint16_t nDataLen);

/*! 
 *  \brief     ���߿ؼ�-�������
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  channel ͨ����
 */
void GraphChannelDataClear(uint16_t screen_id,uint16_t control_id,uint8_t channel);

/*! 
 *  \brief     ���߿ؼ�-������ͼ����
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  x_offset ˮƽƫ��
 *  \param  x_mul ˮƽ����ϵ��
 *  \param  y_offset ��ֱƫ��
 *  \param  y_mul ��ֱ����ϵ��
 */
void GraphSetViewport(uint16_t screen_id,uint16_t control_id,uint16_t x_offset,uint16_t x_mul,uint16_t y_offset,uint16_t y_mul);

/*! 
 *  \brief     ��ʼ��������
 *  \param  screen_id ����ID
 */
void BatchBegin(uint16_t screen_id);

/*! 
 *  \brief     �������°�ť�ؼ�
 *  \param  control_id �ؼ�ID
 *  \param  value ��ֵ
 */
void BatchSetButtonValue(uint16_t control_id,uint8_t state);

/*! 
 *  \brief     �������½������ؼ�
 *  \param  control_id �ؼ�ID
 *  \param  value ��ֵ
 */
void BatchSetProgressValue(uint16_t control_id,uint32_t value);

/*! 
 *  \brief     �������»������ؼ�
 *  \param  control_id �ؼ�ID
 *  \param  value ��ֵ
 */
void BatchSetSliderValue(uint16_t control_id,uint32_t value);

/*! 
 *  \brief     ���������Ǳ�ؼ�
 *  \param  control_id �ؼ�ID
 *  \param  value ��ֵ
 */
void BatchSetMeterValue(uint16_t control_id,uint32_t value);

/*! 
 *  \brief     ���������ı��ؼ�
 *  \param  control_id �ؼ�ID
 *  \param  strings �ַ���
 */
void BatchSetText(uint16_t control_id,uint8_t *strings);

/*! 
 *  \brief     �������¶���\ͼ��ؼ�
 *  \param  control_id �ؼ�ID
 *  \param  frame_id ֡ID
 */
void BatchSetFrame(uint16_t control_id,uint16_t frame_id);

/*! 
 *  \brief    ������������
 */
void BatchEnd(void);

/*! 
 *  \brief     ���õ���ʱ�ؼ�
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  timeout ����ʱ(��)
 */
void SeTimer(uint16_t screen_id,uint16_t control_id,uint32_t timeout);

/*! 
 *  \brief     ��������ʱ�ؼ�
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void StartTimer(uint16_t screen_id,uint16_t control_id);

/*! 
 *  \brief     ֹͣ����ʱ�ؼ�
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void StopTimer(uint16_t screen_id,uint16_t control_id);

/*! 
 *  \brief     ��ͣ����ʱ�ؼ�
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 */
void PauseTimer(uint16_t screen_id,uint16_t control_id);

/*! 
 *  \brief     ���ÿؼ�����ɫ
 *  \details  ֧�ֿؼ������������ı�
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  color ����ɫ
 */
void SetControlBackColor(uint16_t screen_id,uint16_t control_id,uint16_t color);

/*! 
 *  \brief     ���ÿؼ�ǰ��ɫ
  * \details  ֧�ֿؼ���������
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  color ǰ��ɫ
 */
void SetControlForeColor(uint16_t screen_id,uint16_t control_id,uint16_t color);

/*! 
 *  \brief     ��ʾ\���ص����˵��ؼ�
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  show �Ƿ���ʾ��Ϊ0ʱfocus_control_id��Ч
 *  \param  focus_control_id �������ı��ؼ�(�˵��ؼ�������������ı��ؼ�)
 */
void ShowPopupMenu(uint16_t screen_id,uint16_t control_id,uint8_t show,uint16_t focus_control_id);

/*! 
 *  \brief     ��ʾ\����ϵͳ����
 *  \param  show 0���أ�1��ʾ
 *  \param  x ������ʾλ��X����
 *  \param  y ������ʾλ��Y����
 *  \param  type 0С���̣�1ȫ����
 *  \param  option 0�����ַ���1���룬2ʱ������
 *  \param  max_len ����¼���ַ���������
 */
void ShowKeyboard(uint8_t show,uint16_t x,uint16_t y,uint8_t type,uint8_t option,uint8_t max_len);


/*! 
 *  \brief     �������
 *  \param  show 0���أ�1��ʾ
 *  \param  screen_id ����ID
 *  \param  control_id �ؼ�ID
 *  \param  strings ��ӵ����ݣ�������֮���ԡ���������
 */
void SetDataRecode(uint16_t screen_id,uint16_t control_id,uint8_t *strings);

#endif
