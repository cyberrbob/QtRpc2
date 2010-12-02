/***************************************************************************
 *  Copyright (c) 2010, Resara LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Resara LLC nor the
 *       names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL RESARA LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***************************************************************************/
#include "testthread.h"
#include "sleeper.h"

TestThread::TestThread(QObject *parent) : QThread(parent)
{
	thisthing = "Still Alive";
	megaString = "zxcvbnmasdfghjklqwertyuiop";
	_tc = 0;
	_mb = 0;
	for (int i = 0 ; i < 2 ; i++)
	{
		megaString += megaString;
	}
}

void TestThread::setTestCaller(TestCaller* tc)
{
// 	_tc = new TestCaller(*tc, 0);
// 	_tc->moveToThread(this);
	_tc = tc;
}

void TestThread::setMessageBus(ClientMessageBus* mb)
{
	_mb = mb;
}

TestThread::~TestThread()
{
}

void TestThread::run()
{
// 	_tc->init();
	while (true)
	{
		qDebug() << "Iterate";
		Sleeper::usleep(10);
		if (!_tc.isNull())
		{
			_tc->callMegaString();
			_tc->callSomethingElse(_tc, SLOT(functionReturn(uint, ReturnValue)), QByteArray("this is some text that will become binary data"));
		}
		if (!_mb.isNull())
		{
			qDebug() << _mb->callFunction(Signature("megaString(QString)"), Arguments() << megaString);
		}
	}
	deleteLater();
}
