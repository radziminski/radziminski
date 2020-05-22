import React, { useState, useEffect } from 'react';
import { dateToString } from '../utils';
import EventCard from '../components/EventCard';
import Button from '../components/Button';
import { digitToTwoCharString } from '../utils';
import axios from 'axios';

const Day = (props) => {
    const [events, setEvents] = useState([]);

    const getEventsFromCurrDate = () => {
        const reqUrl = `http://localhost:3000/api/events/${props.currDate.getFullYear()}-${digitToTwoCharString(
            props.currDate.getMonth() + 1
        )}-${digitToTwoCharString(props.currDate.getDate())}/`;
        console.log(reqUrl);

        axios
            .get(reqUrl)
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
                setEvents(events);
            });
    };

    useEffect(() => {
        getEventsFromCurrDate();
    }, []);

    const deleteEvent = (id) => {
        const reqUrl = `http://localhost:3000/api/deleteevent/${id}`;
        axios.delete(reqUrl).then((data) => {
            console.log(data);
            getEventsFromCurrDate();
        });
    };

    const { switchView, currDate } = props;
    let renderedEvents = <div className="day-view__msg">There are no events on this day.</div>;

    if (events.length > 0)
        renderedEvents = events.map((el, i) => (
            <EventCard
                key={i}
                id={el.id}
                date={el.date}
                description={el.description}
                onDelete={deleteEvent}
            />
        ));

    return (
        <section className="day-view">
            <h1 className="section-title">Events on {dateToString(currDate)}</h1>
            <div className="day-view__events-box">{renderedEvents}</div>
            <div className="day-view__btns">
                <Button onClick={() => switchView('event', currDate)}>Add New</Button>
                <Button classTypes={['red']} onClick={() => switchView('home', currDate)}>
                    Back
                </Button>
            </div>
        </section>
    );
};

export default Day;
