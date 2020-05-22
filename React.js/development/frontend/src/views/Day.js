import React, { useState, useEffect } from 'react';
import axios from 'axios';
import { withRouter } from 'react-router-dom';
import { dateToString, digitToTwoCharString } from '../utils';
import EventCard from '../components/EventCard';
import Button from '../components/Button';
import SectionTitle from '../components/SectionTitle';

const Day = (props) => {
    // Route Params
    const currDate = new Date(props.match.params.date * 1);

    // State
    const [events, setEvents] = useState([]);
    const [isLoading, setIsLoading] = useState(true);

    // Getting events for given day from server
    const getEventsFromCurrDate = () => {
        const reqUrl = `/api/events/${currDate.getFullYear()}-${digitToTwoCharString(
            currDate.getMonth() + 1
        )}-${digitToTwoCharString(currDate.getDate())}/`;

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
                setIsLoading(false);
            })
            .catch((err) => {
                alert(
                    'Sorry, something went wrong while connecting to server. Please make sure that the server is properly running.'
                );
                setIsLoading(false);
                props.history.push('/home');
            });
    };

    // Getting events as component mounts
    useEffect(() => {
        getEventsFromCurrDate();
        // disablaing message since its a method used in other places too
        // eslint-disable-next-line react-hooks/exhaustive-deps
    }, []);

    const deleteEvent = (id) => {
        const reqUrl = `/api/deleteevent/${id}`;
        setIsLoading(true);
        axios
            .delete(reqUrl)
            .then((data) => {
                setIsLoading(false);
                getEventsFromCurrDate();
            })
            .catch((err) => {
                alert(
                    'Sorry, something went wrong delete request. Please make sure that the server is properly running.'
                );
                setIsLoading(false);
                props.history.push('/home');
            });
    };

    // In case there are no events proper message is displayed
    let renderedEvents = <div className="day-view__msg">There are no events on this day.</div>;

    // In case server fetch is in progress
    if (isLoading) renderedEvents = <div>Loading...</div>;

    // In case there are some events, they are mapped into event cards
    if (events.length > 0)
        renderedEvents = events.map((el, i) => (
            <EventCard
                key={i}
                id={el.id}
                date={el.date}
                description={el.description}
                onDelete={deleteEvent}
                onEdit={() => props.history.push(`/event/${el.date.getTime()}/${el.id}`)}
            />
        ));

    return (
        <section className="day-view">
            <SectionTitle>Events on {dateToString(currDate)}</SectionTitle>

            <div className="day-view__events-box">{renderedEvents}</div>
            <div className="day-view__btns">
                <Button onClick={() => props.history.push(`/event/${currDate.getTime()}`)}>
                    Add New
                </Button>
                <Button
                    classTypes={['red']}
                    onClick={() => props.history.push(`/home/${currDate.getTime()}`)}
                >
                    Back
                </Button>
            </div>
        </section>
    );
};

export default withRouter(Day);
