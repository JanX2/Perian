/*
 *  FFissionDecoder.h
 *
 *  Copyright (c) 2006  David Conrad
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; 
 *  version 2.1 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __FFISSIONDECODER_H__
#define __FFISSIONDECODER_H__

#include "FFissionCodec.h"
#include "avcodec.h"
#include "RingBuffer.h"

class FFissionDecoder : public FFissionCodec
{
public:
	FFissionDecoder(UInt32 inInputBufferByteSize = 76800);
	virtual ~FFissionDecoder();
	
	virtual void Initialize(const AudioStreamBasicDescription* inInputFormat, const AudioStreamBasicDescription* inOutputFormat, const void* inMagicCookie, UInt32 inMagicCookieByteSize);
	virtual void Uninitialize();
	virtual void Reset();
	
	virtual void GetProperty(AudioCodecPropertyID inPropertyID, UInt32& ioPropertyDataSize, void* outPropertyData);
	virtual void SetMagicCookie(const void* inMagicCookieData, UInt32 inMagicCookieDataByteSize);
	
	virtual void SetCurrentInputFormat(const AudioStreamBasicDescription& inInputFormat);
	virtual void SetCurrentOutputFormat(const AudioStreamBasicDescription& inOutputFormat);
	virtual UInt32 GetVersion() const;

	virtual void AppendInputData(const void* inInputData, UInt32& ioInputDataByteSize, UInt32& ioNumberPackets, const AudioStreamPacketDescription* inPacketDescription);
	virtual UInt32 ProduceOutputPackets(void* outOutputData, UInt32& ioOutputDataByteSize, UInt32& ioNumberPackets, AudioStreamPacketDescription* outPacketDescription);
	
private:
	void SetupExtradata(OSType formatID);
	int ConvertXiphVorbisCookie();
	void OpenAVCodec();
	
	UInt32 kIntPCMOutFormatFlag;
	Byte *magicCookie;
	UInt32 magicCookieSize;
	
	RingBuffer inputBuffer;
	Byte *outputBuffer;
	int outBufSize;
	int outBufUsed;
	bool dtsPassthrough;
};

// kAudioCodecPropertyHasVariablePacketByteSizes is queried before our input format is set,
// so we can't use that to determine our answer...
class FFissionVBRDecoder : public FFissionDecoder
{
public:
	FFissionVBRDecoder() : FFissionDecoder() { }
	virtual void GetProperty(AudioCodecPropertyID inPropertyID, UInt32& ioPropertyDataSize, void* outPropertyData);
};

#endif
