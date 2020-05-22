import React, { useState, useEffect } from 'react';
import { getMonthStringFromDate, addDaysToDate, compareDates } from '../utils';
import { IoIosArrowDropleft, IoIosArrowDropright } from 'react-icons/io';
import axios from 'axios';

export const Calendar = (props) => {
    const [currDate, setCurrDate] = useState(props.currDate);
    const [daysWithEvents, setDaysWithEvents] = useState([]);

    useEffect(() => {
        axios
            .get('http://localhost:3000/api/events')
            .then((data) => data.data.data)
            .then((data) => JSON.parse(data))
            .then((data) => {
                const events = data.map((el) => {
                    return {
                        id: el.Id,
                        description: el.Description,
                        date: new Date(el.Date),
                    };
                });
                setDaysWithEvents(events);
            });
    }, []);

    const generateDays = (events = []) => {
        const days = [];
        const date = new Date(currDate);
        date.setDate(1);
        // Starting from some days from previous month:
        while (date.getDay() !== 1) date.setDate(date.getDate() - 1);

        // Generating the days:
        const daysRows = 6;
        const daysInWeek = 7;

        let dayCounter = 0;
        while (dayCounter < daysRows * daysInWeek) {
            let hasEvent = false;

            if (events.find((el) => compareDates(el.date, date))) hasEvent = true;

            days.push({
                date: date.getDate(),
                active: date.getMonth() === currDate.getMonth(),
                event: hasEvent,
            });
            addDaysToDate(date, 1);
            dayCounter++;
        }
        return days;
    };

    const onDayClicked = (e) => {
        const day = e.target.innerText;
        let month = currDate.getMonth();
        let year = currDate.getFullYear();
        if (e.target.getAttribute('data-isactive') === 'false') {
            if (day > 20) month--;
            else month++;
        }
        if (month > 11) {
            month = 0;
            year++;
        }
        if (month < 0) {
            month = 11;
            year--;
        }

        props.switchView('day', new Date(year, month, day));
    };

    const onMonthChanged = (offset) => {
        const date = new Date(currDate);
        let newMonth = date.getMonth() + offset;
        if (newMonth > 11) {
            newMonth = 0;
            date.setFullYear(date.getFullYear() + 1);
        }
        if (newMonth < 0) {
            newMonth = 11;
            date.setFullYear(date.getFullYear() - 1);
        }
        date.setMonth(newMonth);

        setCurrDate(date);
    };

    const days = generateDays(daysWithEvents).map(({ date, active, event }, i) => (
        <div
            key={i}
            className={`calendar__day ${!active ? 'calendar__day--ghost' : ''} ${
                event ? 'calendar__day--event' : ''
            }`}
            onClick={onDayClicked}
            data-isactive={active}
        >
            {date}
        </div>
    ));

    return (
        <div className="calendar">
            <div className="calendar__navbar">
                <div className="calendar__arrow" onClick={() => onMonthChanged(-1)}>
                    <IoIosArrowDropleft className="calendar__icon" />
                </div>
                <h1 className="calendar__title">{getMonthStringFromDate(currDate)}</h1>
                <div className="calendar__arrow" onClick={() => onMonthChanged(1)}>
                    <IoIosArrowDropright className="calendar__icon" />
                </div>
            </div>
            <div className="calendar__days-box">{days}</div>
        </div>
    );
};

export default Calendar;
