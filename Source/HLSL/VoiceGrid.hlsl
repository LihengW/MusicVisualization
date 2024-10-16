# define PI 3.1415

particlepos = ParticlePosition + SystemPosition;
particlepos.z = 15.0f * sin((2.0f * ParticlePosition.y + 2.0f * ParticlePosition.x) * PI + 3.0f * Time);