﻿/*
 * Copyright (c) 2021 Belledonne Communications SARL.
 *
 * This file is part of linphone-desktop
 * (see https://www.linphone.org).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONFERENCE_SCHEDULER_MODEL_H_
#define CONFERENCE_SCHEDULER_MODEL_H_

#include <linphone++/linphone.hh>
#include <QDateTime>
#include <QObject>

class ConferenceSchedulerModel : public QObject
								, public linphone::ConferenceSchedulerListener
{
	Q_OBJECT
	
public:
	static std::shared_ptr<ConferenceSchedulerModel> create(QObject *parent = Q_NULLPTR);
	ConferenceSchedulerModel (QObject * parent = nullptr);
	~ConferenceSchedulerModel ();
	std::shared_ptr<linphone::ConferenceScheduler> getConferenceScheduler();
	
	virtual void onStateChanged(const std::shared_ptr<linphone::ConferenceScheduler> & conferenceScheduler, linphone::ConferenceSchedulerState state) override;
	virtual void onInvitationsSent(const std::shared_ptr<linphone::ConferenceScheduler> & conferenceScheduler, const std::list<std::shared_ptr<linphone::Address>> & failedInvitations) override;

signals:
	void stateChanged(linphone::ConferenceSchedulerState state);
	void invitationsSent(const std::list<std::shared_ptr<linphone::Address>> & failedInvitations);

private:
	std::shared_ptr<linphone::ConferenceScheduler> mConferenceScheduler;
	std::weak_ptr<ConferenceSchedulerModel> mSelf;		// Used for Linphone Listener
	
};

Q_DECLARE_METATYPE(std::shared_ptr<ConferenceSchedulerModel>)

#endif
