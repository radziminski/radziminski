import React, { useState, useEffect, Fragment } from 'react';
import TextInput from '../components/TextInput';
import { dateToString } from '../utils';
import Button from '../components/Button';
import TimeInput from '../components/TimeInput';
import axios from 'axios';
import { withRouter } from 'react-router-dom';

const Event = (props) => {
    // Route Params
    // Getting proper params from route
    const currDate = props.match.params.date ? new Date(props.match.params.date * 1) : new Date();

    // id is supplied only if event is edited
    const id = props.match.params.id || null;

    // Default time is 00:00
    const defaultTime = new Date();
    defaultTime.setHours(0, 0, 0, 0);

    // State
    const [description, setDescription] = useState(props.description || '');
    const [time, setTime] = useState(defaultTime);
    const [isLoading, setIsLoading] = useState(false);

    // Used only if id is supplied - event is edited - getting fresh event data from server
    useEffect(() => {
        if (id) {
            const reqUrl = `/api/event/${id}`;
            setIsLoading(true);
            axios
                .get(reqUrl)
                .then((data) => JSON.parse(data.data.data))
                .then((data) => {
                    setDescription(data.Description);
                    const newTime = new Date(data.Date);
                    setTime(newTime);
                    setIsLoading(false);
                })
                .catch((err) => {
                    alert(
                        'Sorry, event with given id does not exist. Please make sure that the server is properly running.'
                    );
                    setIsLoading(false);
                    props.history.push('/home');
                });
        }
    }, [id, props.history]);

    // Updateing/Adding new event on server
    const onSubmit = (e) => {
        e.preventDefault();
        if (id) return updateEvent(id);
        addNewEvent();
    };

    // Creating content type form for POST or PUT requests
    const getFormData = () => {
        //int Year, int Month, int Day, int Hours, int Minutes, string Description
        const data = new FormData();
        data.set('Year', currDate.getFullYear());
        data.set('Month', currDate.getMonth() + 1);
        data.set('Day', currDate.getDate());
        data.set('Hours', time.getHours());
        data.set('Minutes', time.getMinutes());
        data.set('Description', description);
        return data;
    };

    // Sending PUT request for event update
    const updateEvent = (id) => {
        const reqUrl = `/api/updateevent/${id}`;
        const data = getFormData();
        setIsLoading(true);
        axios
            .put(reqUrl, data, {
                headers: {
                    'Content-Type': 'multipart/form-data',
                },
            })
            .then((data) => {
                setIsLoading(false);
                props.history.push(`/day/${currDate.getTime()}`);
            })
            .catch((err) => {
                alert(
                    'Something went wrong while sending the request. Please check if server is running properly.'
                );
                setIsLoading(false);
                props.history.push('/home');
            });
    };

    // Sending POST request for event creation
    const addNewEvent = () => {
        const reqUrl = `/api/addevent`;
        const data = getFormData();
        setIsLoading(true);
        axios
            .post(reqUrl, data, {
                headers: {
                    'Content-Type': 'multipart/form-data',
                },
            })
            .then((data) => {
                setIsLoading(false);
                props.history.push(`/day/${currDate.getTime()}`);
            })
            .catch((err) => {
                alert(
                    'Something went wrong while sending the request. Please check if server is running properly.'
                );
                setIsLoading(false);
                props.history.push('/home');
            });
    };

    const title = id ? 'Editing Event' : 'New Event';
    const sendBtnText = id ? 'Update' : 'Send';

    let inputs = (
        <Fragment>
            <TimeInput label="Time: " onChange={setTime} default={time} />
            <TextInput onChange={setDescription} label="Description: " defaultValue={description} />
        </Fragment>
    );
    if (isLoading) inputs = <div>Loading...</div>;

    return (
        <section className="event-view">
            <h1 className="section-title">
                {title} on {dateToString(currDate)}
            </h1>
            <form className="event-view__form" onSubmit={onSubmit}>
                {inputs}

                <div className="event-view__btns">
                    <Button type="submit" classTypes={['green']}>
                        {sendBtnText}
                    </Button>
                    <Button
                        classTypes={['red']}
                        onClick={() => props.history.push(`/day/${currDate.getTime()}`)}
                    >
                        Cancel
                    </Button>
                </div>
            </form>
        </section>
    );
};

export default withRouter(Event);
