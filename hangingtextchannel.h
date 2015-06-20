/**
 * telepathy-hanging
 *
 * Copyright (C) 2015 Tiago Salem Herrmann, All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranties of MERCHANTABILITY,
 * SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef HANGINGTEXTCHANNEL_H
#define HANGINGTEXTCHANNEL_H

#include <QObject>

#include <TelepathyQt/Constants>
#include <TelepathyQt/BaseChannel>
#include <TelepathyQt/Types>
#include <TelepathyQt/DBusError>
#include <QString>

#include "connection.h"
#include <hangishclient.h>

class HangingConnection;

class HangingTextChannel : public QObject
{
    Q_OBJECT
public:
    HangingTextChannel(HangingConnection *conn, const QString &conversationId, const QString userChatId, QStringList phoneNumbers, QObject *parent = 0);

    //telepathy callbacks
    QString sendMessage(Tp::MessagePartList message, uint flags, Tp::DBusError* error);
    void onAddMembers(const Tp::UIntList& handles, const QString& message, Tp::DBusError* error);
    void onRemoveMembers(const Tp::UIntList& handles, const QString& message, Tp::DBusError* error);
    void setChatState(uint state, Tp::DBusError *error);

    void eventReceived(ClientEvent &event, bool scrollback = false);
    void updateTypingState(const ClientSetTypingNotification &notification);
    Tp::BaseChannelPtr baseChannel();
    void sendDeliveryReport(const QString &messageId, QString identifier, Tp::DeliveryStatus status);
    void addMembers(QStringList phoneNumbers);
    Tp::UIntList members();
    QString conversationId();

private Q_SLOTS:
    void onTypingTimeout();

private:
    ~HangingTextChannel();
    Tp::BaseChannelPtr mBaseChannel;
    HangingConnection *mConnection;
    QStringList mParticipants;
    uint mMessageCounter;
    Tp::UIntList mMembers;
    QString mConversationId;
    QString mUserChatId;
    QMap<uint, QString> mPendingMessages;
    QTimer mTypingTimer;

    Tp::BaseChannelMessagesInterfacePtr mMessagesIface;
    Tp::BaseChannelGroupInterfacePtr mGroupIface;
    Tp::BaseChannelTextTypePtr mTextChannel;
    Tp::BaseChannelRoomInterfacePtr mRoomIface;
    Tp::BaseChannelRoomConfigInterfacePtr mRoomConfigIface;
    Tp::BaseChannelChatStateInterfacePtr mChatStateIface;
};

#endif // HANGINGTEXTCHANNEL_H
