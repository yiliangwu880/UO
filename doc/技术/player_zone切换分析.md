
# ����л�����
## �ҵ����
	�趨��������������ೡ���������ȶ���崻���������Ͽ����������ǡ�ȫ�����������
## center player
	state: 
		WaitEnterZone:    
				//������, ����zone ��¼player.				--ReqLoginZone_sc
				//���� zone ��¼player �ɹ��� ���� Playing		--RspLoginZone_cs

		Playing,
				//enter:����ת�� ��Ϣ. ����zoneId
				//���� Ԥ����ת��Ŀ��zone.						--ReqZoneReserve
				//���� ��ӦԤ����ת��Դzone, �ɹ�Ԥ������ Moving��--RspZoneReserve

		Moving, //enter:���� send to zone��Ϣ
				//�յ�zone ת�� zone�� ת��Ŀ��zone ������Playing	--ReqTranZone

## zone Player
	state: 
		None   : //���� ReqZoneReserve,�ɹ�����WaitTranIn��ʧ��֪ͨcenter --RspZoneReserve
				//���� ��¼player������ Playing

		WaitTranIn:  //���� ReqTranZone�� ����acc�ָ�,����acc ����, ����Playing.  --MsgReqCacheMsg

		Playing: 
				//����acc ���棬���� center Ԥ��λ��,����WaitReserve��		--MsgReqCacheMsg�� ReqZoneReserve

		WaitReserve: (��ֹ�ظ�����Ԥ��)
				// ������Ӧ acc����, center Ԥ����ok�� ���� ת��zone. ɾ���Լ��� --RspZoneReserve��MsgRspCacheMsg��ReqTranZone
					(��֤ ɾ���󣬲����յ� Player ��ҵ������)
				//����center Ԥ��ʧ�ܣ�����Playing.				--RspZoneReserve