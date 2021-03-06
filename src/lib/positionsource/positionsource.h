/*
 * Copyright 2019 Patrick José Pereira <patrickjp@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QGeoPositionInfoSource>
#include <QSharedPointer>

class QJSEngine;
class QQmlEngine;

/**
 * @brief Manage the position source of the ground control station.
 *
 */
class PositionSource : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate NOTIFY coordinateChanged)

public:
    /**
     * @brief Return PositionSource status, if it's enabled.
     *
     * @return true PositionSource is enable and working.
     * @return false Positionsource is disabled.
     */
    bool enabled() const;

    /**
     * @brief Turn PositionSource to enable or disable.
     *
     * @param enabled
     */
    void setEnabled(bool enabled);

    /**
     * @brief Set a new position info.
     *
     * @param geoPositionInfo
     */
    void setPositionInfo(const QGeoPositionInfo &geoPositionInfo);

    /**
     * @brief Return the last valid coordinate.
     *
     * @return QGeoCoordinate
     */
    QGeoCoordinate coordinate() const;

    /**
     * @brief Return the position source for this class.
     *
     * @return const QGeoPositionInfoSource*
     */
    const QGeoPositionInfoSource *positionInfoSource() const;

    /**
     * @brief Return PositionSource pointer.
     *
     * @return PositionSource*
     */
    static PositionSource &self();

    /**
     * @brief Return a pointer of this singleton to the qml register function.
     *
     * @param engine
     * @param scriptEngine
     * @return QObject*
     */
    static QObject *qmlSingletonRegister(QQmlEngine *engine, QJSEngine *scriptEngine);

Q_SIGNALS:
    void enabledChanged(bool enabled);
    void coordinateChanged(const QGeoCoordinate &geoCoordinate);

private:
    Q_DISABLE_COPY(PositionSource)
    /**
     * @brief Construct a new Position Source object.
     *
     */
    PositionSource();

    /**
     * @brief Create the position source for this class.
     *
     */
    void createPositionSource();

    /**
     * @brief Set position source error type.
     *
     * @param positioningError
     */
    void setPositionSourceError(QGeoPositionInfoSource::Error positioningError);

    bool m_enabled;
    QGeoCoordinate m_geoCoordinate;
    QSharedPointer<QGeoPositionInfoSource> m_geoPositionSource;
};
