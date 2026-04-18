# Space Travel

_SUMMARY: How fast could humans travel to Pluto, or beyond?_ 

## Intro

I was wondering about how space travel is going to evolve in the future.

With the recent Artemis II mission, there's a renewed interest in manned space travel. This
is great to see, but we're also reminded of how _vast_ and _empty_ space is. 

There's 3 levels of travel that I'm interested in:

* Interplanetary - Pluto is ~40 AU away (on average). 

* Interstellar  - Alpha Centauri ~4.2 light-years away. (Fun fact- the nearest known exoplanets are here!)

* Intergalactic - Our nearest neighbor Andromeda is ~2.5 million light-years away (!!)

Propulsion advances are necessary -- we've been making incremental improvements on
chemical rockets for 50+ years but there is a well-defined ceiling from both
thermodynamics and the rocket equation. We just aren't going _fast_ enough.

But let's ignore that for now and say we have limitless propulsion on our side. This
is futuristic but not in the fantasy realm. As I mention below, we currently have wildly efficient
ion thrusters.
 
Even with this, we are still limited by physics -- the speed of light, human lifespans and acceleration
tolerance, and the scale of our universe.

We're going to assume things like wormholes, FTL travel, gravity manipulation, lifetime extension via
cryosleep/consciousness transfer are non-existent. I want something that could _maybe_ be possible within
my lifetime with current technology. 

## Problem Setup

We are going to measure distance in a 1-D way, ignoring any gravitational effects.

Let's start by assuming a spacecraft that accelerates at ~1g for as long as we want. 
This is about as fast as we can hope to go with humans in the ship, but perhaps we could
give ourselves a little speed boost by bumping acceleration up to 12 m/s^2. 1.22 G's would
probably take a physical toll (a weight of 150lb on earth would be 183lb in this ship).

That's our maximum acceleration, let's also set a speed limit. Of course the most optimistic
and sci-fi one would be the speed of light, but we can be slightly more reasonable by assuming
we can get to 0.1c. 

If that is our maximum acceleration, then the fastest way to get from point A to point B is to 
just accelerate continuously until we are halfway, then immediately start decelerating so we 
don't blow past our target. If the distance is large, we will coast at our max speed for a bit.

Another simplifying assumption-- our acceleration is a constant and we start and end at V = 0.
So, for large distances our speed vs time plot would look like this:

```
   -----------
  /           \
 /             \
/               \
```

And for smaller distances where we don't reach V_max, it'll look like this:

```
  /\
 /  \
/    \
```

To get our total time we just need to find t_end such that the integral of this graph
is D. We can calculate this from basic kinematic equations and geometry.

## Time Dilation

The 0.1c, 1g spacecraft can make it to Pluto and back in around a month. That's great news, and 
means we could easily explore our solar system with ships like that! But the picture gets bleaker when
looking at interstellar travel. Now we're talking 40+ years-- one-way. Not great. A ship that could house people
for that long would have to be enormous, and now we're getting a bit into sci-fi.

But then I remembered that due to Special Relativity, you get more time dilation the faster you go. How much
time could we save our explorers for, say the 8 light-year round trip to and from Proxima Centauri? Turns out,
not that much unless you're going really far and really fast. Due to the acceleration and deceleration phases,
our average speed is not going to be that close to the speed of light, and our Lorentz factor isn't very high.

Example: Even if our max speed was 0.999c, our 4.2 light-year trip would still take 2.73 years from the 
perspective of our explorers. That's because it takes almost a year to accelerate from 0 to C at 1.2 G's!

Each one of the 3 travel scales I mentioned are orders of magnitude apart. 

Exploring our solar system is possible on the timescale of a month or less. 

For our nearest neighbor stars and exoplanets, a couple years pass for the explorers even
with time dilation and near light-speed travel.

For traveling to Andromeda, even at 0.9999c we are still talking _thousands_ of years and many
generations of humans aboard the ship. Pure science fiction.

Thankfully there are... *checks Wikipedia*... around 100 billion stars in the Milky Way, with a diameter of
around 87 thousand light-years. Plenty of stuff to explore there.

Final note: The times displayed are just for one-way travel, so double that if you're just planning
to turn back around.

## Propulsion Types

Side note, I used to be a big fan of nuclear-thermal engines (NERVA style), but
nowadays I'm starting to think that electric/ion propulsion powered by nuclear reactors 
might be the way to go. Highest Isp is what we need. Electric propulsion can already do burn times
on the order of months. We just have to get the thrust up to we can accelerate a large craft at a 
constant 1g.

In general, I think assuming in the future that we will have ways of generating vast
electrical power at a low mass cost is a safe bet.

## Robots

This is why sending robotic probes just makes sense. The craft can be lighter, 
easier to design, accelerate faster, and not waste months of time going somewhere
that may not be of interest.

I think making human-carrying vehicles is necessary, but most of our farthest exploring will
likely continue to be done via autonomous probes.
